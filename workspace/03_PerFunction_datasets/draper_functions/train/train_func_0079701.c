LineToIndex(int line) const
{
   if (line < 0 || line >= (int) mLines.GetCount())
   {
      return wxNOT_FOUND;
   }

   return mLines[line]->index;
}
