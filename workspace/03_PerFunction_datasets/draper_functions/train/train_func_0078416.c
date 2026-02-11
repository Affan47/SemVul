QtUtilGetNumStrWidth (QPainter const *pPainter, QFont const *pFont, int IntLen, int FrcLen, bool Signed, int *pDx)
{
   QString Str;
   int     Digits;

   Digits = IntLen + FrcLen;
   if (FrcLen > 0) Digits++;
   if (Signed    ) Digits++;

   Str.sprintf ("%0*.*f", Digits, FrcLen, 0.0);
   Str.replace ('.', ',');

   CHK (QtUtilGetTextSize (pPainter, pFont, Str, pDx, NULL))

   return NO_ERROR;
}
