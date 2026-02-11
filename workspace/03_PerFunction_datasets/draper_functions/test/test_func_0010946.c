tty_break (void)
{
   struct termios modmodes;

   if (tcgetattr(fileno(stdin), &savemodes) < 0)
   {
      return -1;
   }
   havemodes = 1;

   hidecursor();


   modmodes = savemodes;
   modmodes.c_lflag &= ~ICANON;
   modmodes.c_lflag &= ~ECHO;
   modmodes.c_cc[VMIN] = 1;
   modmodes.c_cc[VTIME] = 0;

   return tcsetattr(fileno(stdin), TCSANOW, &modmodes);
}
