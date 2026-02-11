RtlWriteModel( RtlFigure )

  rtlfig_list *RtlFigure;
{
  rtlmod_list  *ScanMod;
  rtlport_list *ScanPort;
  rtlgen_list  *ScanGen;

  for ( ScanMod  = RtlFigure->MODEL;
        ScanMod != (rtlmod_list *)0;
        ScanMod  = ScanMod->NEXT )
  {
    fprintf( RtlFile, "MODEL\t%ld\t%s\n",
             (long)ScanMod->FLAGS,
             ScanMod->NAME );

    for ( ScanPort  = ScanMod->PORT;
          ScanPort != (rtlport_list *)0;
          ScanPort  = ScanPort->NEXT )
    {
      fprintf( RtlFile, "PORT\t%ld\t%ld\t%ld",
               (long)ScanPort->DIR,
               (long)ScanPort->BASE,
               (long)ScanPort->FLAGS );

      RtlWriteExpr( "", ScanPort->VEX_ATOM );
    }

    for ( ScanGen  = ScanMod->GENERIC;
          ScanGen != (rtlgen_list *)0;
          ScanGen  = ScanGen->NEXT )
    {
      fprintf( RtlFile, "GEN_MOD\t%ld\t%ld\t",
               (long)ScanGen->BASE,
               (long)ScanGen->FLAGS );

      RtlWriteExpr( "", ScanGen->VEX_ATOM );

      RtlWriteExpr( "GEN_EXPR", ScanGen->VEX_EXPR );
    }
  }
}
