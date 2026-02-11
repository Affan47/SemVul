SigWinch(int)
{

#ifdef TIOCGWINSZ
   struct winsize ws;

   if (ioctl(1, TIOCGWINSZ, &ws) != -1 && ws.ws_col >= 5)
      ScreenWidth = ws.ws_col - 1;
#endif
}
