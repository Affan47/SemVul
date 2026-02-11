winch_cleanup(void)
{
#if	defined(SIGWINCH) && defined(TIOCGWINSZ)
    if(ready_for_winch)
      longjmp(winch_state, 1);
    else
      winch_occured = 1;
#endif
}
