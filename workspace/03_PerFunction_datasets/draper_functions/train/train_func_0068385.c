trapdebug(int dummy)
{
  ptype_list *ScanDebug;

  for ( ScanDebug  = HEAD_MBKDEBUG;
        ScanDebug != (ptype_list *)NULL;
        ScanDebug  = ScanDebug->NEXT )
  {
    fprintf( stdout, "mbkdebug: file %s line %ld\n",
             (char *)ScanDebug->DATA, ScanDebug->TYPE );
  }

  fflush( stdout );

  signal( SIGQUIT, trapdebug );
  signal( SIGSEGV, SIG_DFL      );
  signal( SIGBUS , SIG_DFL      );
  signal( SIGILL , SIG_DFL      );
}
