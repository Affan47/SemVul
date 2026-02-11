scrollToRow(XmIconListWidget _ilw, int _row,
                           Boolean _jump, Boolean _toTop)
#else
static void scrollToRow(_ilw, _row, _jump, _toTop)
XmIconListWidget _ilw;
int _row;
Boolean _jump;
Boolean _toTop;
#endif
{
   int rowsPerClip;
   int value, ss, inc, pi;
   int newRow;
   Boolean fromTop;

   if (CLIP(_ilw) == NULL)
      return;

   if (!_toTop && rowFullyVisible(_ilw, _row, &fromTop))
      return;

   rowsPerClip = HEIGHT(CLIP(_ilw))/FULL_EL_HEIGHT(_ilw);

   if (_toTop)
   {
      if (_row >= rowsPerClip)
      {
         if (((NUM_ELEMENTS(_ilw) - _row) - 1) < rowsPerClip)
            newRow = NUM_ELEMENTS(_ilw) - rowsPerClip;
         else
            newRow = _row;
      }
      else
      {
         if (NUM_ELEMENTS(_ilw) > rowsPerClip)
            newRow = _row;
         else
            newRow = 0;
      }
   }
   else
   if (fromTop)
      newRow = _row;
   else
   {
      newRow = _row - (rowsPerClip-1);
      if (newRow < 0)
         newRow = 0;
   }

   XmScrollBarGetValues(VBAR(_ilw), &value, &ss, &inc, &pi);
   XmScrollBarSetValues(VBAR(_ilw), newRow, ss, inc, pi, TRUE);


}
