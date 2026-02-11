SingleMethodExecute()
{
  ThreadIdType                 thread_loop = 0;
  ThreadProcessIDType process_id[ITK_MAX_THREADS];

  if ( !m_SingleMethod )
    {
    itkExceptionMacro(<< "No single method set!");
    }


  m_NumberOfThreads = std::min( m_GlobalMaximumNumberOfThreads, m_NumberOfThreads );


  bool        exceptionOccurred = false;
  std::string exceptionDetails;
  try
    {
    for ( thread_loop = 1; thread_loop < m_NumberOfThreads; thread_loop++ )
      {
      m_ThreadInfoArray[thread_loop].UserData    = m_SingleData;
      m_ThreadInfoArray[thread_loop].NumberOfThreads = m_NumberOfThreads;
      m_ThreadInfoArray[thread_loop].ThreadFunction = m_SingleMethod;

      process_id[thread_loop] =
        this->DispatchSingleMethodThread(&m_ThreadInfoArray[thread_loop]);
      }
    }
  catch ( std::exception & e )
    {

    exceptionDetails = e.what();


    exceptionOccurred = true;
    }
  catch ( ... )
    {


    exceptionOccurred = true;
    }


  try
    {
    m_ThreadInfoArray[0].UserData = m_SingleData;
    m_ThreadInfoArray[0].NumberOfThreads = m_NumberOfThreads;
    m_SingleMethod( (void *)( &m_ThreadInfoArray[0] ) );
    }
  catch ( ProcessAborted & )
    {


    for ( thread_loop = 1; thread_loop < m_NumberOfThreads; thread_loop++ )
      {
      try
        {
        this->WaitForSingleMethodThread(process_id[thread_loop]);
        }
      catch ( ... )
              {}
      }

    throw;
    }
  catch ( std::exception & e )
    {

    exceptionDetails = e.what();


    exceptionOccurred = true;
    }
  catch ( ... )
    {


    exceptionOccurred = true;
    }


  for ( thread_loop = 1; thread_loop < m_NumberOfThreads; thread_loop++ )
    {
    try
      {
      this->WaitForSingleMethodThread(process_id[thread_loop]);
      if ( m_ThreadInfoArray[thread_loop].ThreadExitCode
           != ThreadInfoStruct::SUCCESS )
        {
        exceptionOccurred = true;
        }
      }
    catch ( std::exception & e )
      {

      exceptionDetails = e.what();
      exceptionOccurred = true;
      }
    catch ( ... )
      {
      exceptionOccurred = true;
      }
    }

  if ( exceptionOccurred )
    {
    if ( exceptionDetails.empty() )
      {
      itkExceptionMacro("Exception occurred during SingleMethodExecute");
      }
    else
      {
      itkExceptionMacro(<< "Exception occurred during SingleMethodExecute" << std::endl << exceptionDetails);
      }
    }
}
