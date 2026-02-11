getWrappedString(const string& str, int leftSpace, bool spacesInFirstLine) const
{
   string result;
   insert_iterator<string> iIt(result, result.begin());
   string::const_iterator sIt;

   int col = leftSpace;

   if (spacesInFirstLine)
   {
      for (int i = 0; i < leftSpace; ++i)
         *iIt++ = ' ';
   }

   for (sIt = str.begin(); sIt != str.end(); ++sIt)
   {
      if ( (*sIt == ' ' && col > _maxColumns) || *sIt == '\n' )
      {
         col = leftSpace;
         *iIt++ = '\n';
         for (int i = 0; i < leftSpace; ++i)
            *iIt++ = ' ';
      }
      else
      {
         ++col;
         *iIt++ = *sIt;
      }
   }

   return result;
}
