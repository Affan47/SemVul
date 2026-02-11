check(const char* msg)
{

  if (msg) TRACE_ERR( msg << " : ");


  TRACE_ERR( "[" << (running ? elapsed_time() : 0) << "] seconds\n");
}
