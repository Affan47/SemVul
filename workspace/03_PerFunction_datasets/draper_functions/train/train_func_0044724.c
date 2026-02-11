launch_pipes(int *pipes, int flag)
#else
static int launch_pipes(pipes, flag)
     int *pipes;
     int flag;
#endif
{
  int i;
  char tbuf[SZ_LINE];
  if( pipes ){
    for(i=0; i<4; i++){
      pipes[i] = -1;
    }
    if( (pipe(&pipes[0]) < 0) || (pipe(&pipes[2]) < 0) ) return -1;
    if( flag ){
#if HAVE_SETENV
      snprintf(tbuf, SZ_LINE-1, "%d,%d,%d,%d",
	       pipes[0], pipes[1], pipes[2], pipes[3]);
      setenv("LAUNCH_PIPES", tbuf, 1);
#else
      snprintf(tbuf, SZ_LINE-1, "LAUNCH_PIPES=%d,%d,%d,%d",
	       pipes[0], pipes[1], pipes[2], pipes[3]);
      putenv(xstrdup(tbuf));
#endif
    }
  }
  return 0;
}
