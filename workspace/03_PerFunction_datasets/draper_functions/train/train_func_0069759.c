MochaCtlAblArrayHashSupport( AblArray )

  ablarray *AblArray;
{
  long Index;

  if ( AblArray == (ablarray *)0 ) return;

  for ( Index = 0; Index < AblArray->WIDTH; Index++ )
  {
    MochaCtlAblHashSupport( AblArray->ARRAY[ Index ] );
  }
}
