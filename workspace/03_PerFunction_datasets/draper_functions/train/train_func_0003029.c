main(int argc VL_UNUSED, char** argv VL_UNUSED)
{
#ifndef VL_DISABLE_THREADS
#if defined(VL_THREADS_POSIX)
  vl_uindex i ;
  pthread_t threads [5] ;
  int threadIds [5] ;
  for (i = 0 ; i < sizeof(threads) / sizeof(threads[0]) ; ++i) {
    threadIds [i] = i ;
    pthread_create (threads + i, NULL, testThread, threadIds + i) ;
  }
  for (i = 0 ; i < sizeof(threads) / sizeof(threads[0]) ; ++i) {
    pthread_join (threads[i], NULL) ;
  }
#elif defined(VL_THREADS_WIN)
  int i ;
  DWORD threadIds [5] ;
  HANDLE threadHandles [5] ;
  for (i = 0 ; i < sizeof(threadHandles) / sizeof(threadHandles[0]) ; ++i) {
    threadHandles [i] = CreateThread (
      NULL, 0,
      testThread, threadIds + i,
      0, threadIds + i) ;
  }
  for (i = 0 ; i < sizeof(threadHandles) / sizeof(threadHandles[0]) ; ++i) {
    WaitForSingleObject (threadHandles[i], INFINITE);
  }
#endif

#else
  printf("VLFeat was compiled without threading support\n") ;
#endif
  {
    char * string = vl_configuration_to_string_copy() ;
    printf("%s", string) ;
    vl_free(string) ;
  }
  return 0 ;
}
