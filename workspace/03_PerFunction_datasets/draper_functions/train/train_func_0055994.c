sys_getch( void )
{
  char ch = 0;
#if SFEPY_PLATFORM == 0
  if (read (STDERR_FILENO, &ch, 1) < 0) {
    return( RET_Fail );
  }
#endif
  return( ch );
}
