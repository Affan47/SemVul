GetGlobalDefaultNumberOfThreads()
{


  if ( m_GlobalDefaultNumberOfThreads != 0 )
    {
    return m_GlobalDefaultNumberOfThreads;
    }


  std::vector<std::string> ITK_NUMBER_OF_THREADS_ENV_LIST;
  itksys_stl::string itkNumberOfThreadsEvnListString = "";
  if ( itksys::SystemTools::GetEnv("ITK_NUMBER_OF_THREADS_ENV_LIST",
                                   itkNumberOfThreadsEvnListString) )
    {

    itkNumberOfThreadsEvnListString += ":ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS";
    }
  else
    {
    itkNumberOfThreadsEvnListString = "NSLOTS:ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS";
    }
    {
    std::stringstream numberOfThreadsEnvListStream(itkNumberOfThreadsEvnListString);
    std::string item;
    while(std::getline(numberOfThreadsEnvListStream, item, ':'))
      {
      if(item.size() > 0)
        {
        ITK_NUMBER_OF_THREADS_ENV_LIST.push_back(item);
        }
      }
    }


  itksys_stl::string itkGlobalDefaultNumberOfThreadsEnv = "0";

  for( std::vector<std::string>::const_iterator lit=ITK_NUMBER_OF_THREADS_ENV_LIST.begin();
    lit != ITK_NUMBER_OF_THREADS_ENV_LIST.end();
    ++lit)
    {
    if ( itksys::SystemTools::GetEnv(lit->c_str(), itkGlobalDefaultNumberOfThreadsEnv) )
      {
      m_GlobalDefaultNumberOfThreads =
        static_cast<ThreadIdType>( atoi( itkGlobalDefaultNumberOfThreadsEnv.c_str() ) );
      }
    }


  if ( m_GlobalDefaultNumberOfThreads <= 0 )
    {
    const ThreadIdType num = GetGlobalDefaultNumberOfThreadsByPlatform();
    m_GlobalDefaultNumberOfThreads = num;
    }


  m_GlobalDefaultNumberOfThreads  = std::min( m_GlobalDefaultNumberOfThreads,
                                              m_GlobalMaximumNumberOfThreads );


  m_GlobalDefaultNumberOfThreads  = std::max( m_GlobalDefaultNumberOfThreads,
                                              NumericTraits<ThreadIdType>::One );

  return m_GlobalDefaultNumberOfThreads;
}
