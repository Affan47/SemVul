ioniceProcess( const char* cmd )
{


  int pid = 0;
  int class = 2;
  int priority = 0;
  if(sscanf( cmd, "%*s %d %d %d", &pid, &class, &priority ) < 2) {
    output( "4\t%d\n", pid );
    return;
  }

#ifdef HAVE_IONICE
  if(pid < 1 || class < 0 || class > 3) {
    output( "4\t%d\n", pid );
    return;
  }

  if (ioprio_set(IOPRIO_WHO_PROCESS, pid, priority | class << IOPRIO_CLASS_SHIFT) == -1) {
    switch ( errno ) {
      case EINVAL:
        output( "4\t%d\n", pid );
        break;
      case ESRCH:
        output( "3\t%d\n", pid );
        break;
      case EPERM:
        output( "2\t%d\n", pid );
        break;
      default:
        output( "1\t%d\n", pid );
        break;
    }
  } else {

    output( "0\t%d\n", pid );
  }
  return;
#else

  output( "1\t%d\n", pid );
  return;
#endif
}
