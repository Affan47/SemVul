QtUtilGetAvgStrWidth (QPainter const *pPainter, QFont const *pFont, int Chars, int *pAvgWidth)
{
   QString AvgChar;
   int     AvgCharWidth;

   AvgChar = "N";
   CHK (QtUtilGetTextSize (pPainter, pFont, AvgChar, &AvgCharWidth, NULL))
   *pAvgWidth = Chars * AvgCharWidth;

   return NO_ERROR;
}
