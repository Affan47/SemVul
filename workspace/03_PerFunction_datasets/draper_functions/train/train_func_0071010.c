menulock(int lock)
{
   if (! lock && ! Fmenulock) zappcrash("menu lock error");
   if (lock && Fmenulock) {
      zmessageACK(mWin,ZTX("prior function still active"));
      return 0;
   }
   if (lock) Fmenulock++;
   else Fmenulock--;
   return 1;
}
