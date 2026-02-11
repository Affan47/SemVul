CifCommandDefineStart()
{
    if ( CifCurrentSymbol != (symbol_list *)NULL )
    {
      ciferror( CIF_ERROR_SYMBOL_STARTED, NULL, CifLineCounter );
    }

    CifCurrentSymbol = CifAddSymbol( CifGetUnsigned() );

    CifSkipSeparator();

    if ( isdigit( (int)CifNextChar ) )
    {
      CifScaleA = CifGetUnsigned();
      CifScaleB = CifGetUnsigned();
    }
    else
    {
      CifScaleA = 1;
      CifScaleB = 1;
    }
}
