TranslateToIndex( const int Value, const wxArrayInt &Choices )
{
   int n = Choices.Index( Value );
   if( n== wxNOT_FOUND )
      n=miNoMatchSelector;
   miNoMatchSelector = 0;
   return n;
}
