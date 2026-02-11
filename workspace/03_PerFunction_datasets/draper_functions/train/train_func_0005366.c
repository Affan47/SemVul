WaitForThread(ThreadProcessIdType threadHandle)
{

  if ( pthread_join(threadHandle, ITK_NULLPTR) )
    {
    itkGenericExceptionMacro(<< "Unable to join thread.");
    }
}
