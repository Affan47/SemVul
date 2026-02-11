VasyGenerateIf( VbhFigure, VbhGenerate )

  vbfig_list  *VbhFigure;
  vbgnr_list  *VbhGenerate;
{
  vbgnr_list *ScanGenerate;
  char       *OldLabel;
  vexexpr    *VexCond;
  int         TrueFalse;

  if ( IsVasyDebugLevel0() )
  {
    VasyPrintf( stdout, "--> VasyGenerateIf %s\n", VbhGenerate->LABEL );
  }

  VexCond = VbhGenerate->IF_COND;
  VasyGenerateSubstConst( VexCond );
  VexCond = simpvexexpr( VexCond );
  VbhGenerate->IF_COND = VexCond;

  VexCond   = VasyGenerateForVexExpr( VexCond );
  TrueFalse = VasyGenerateIsVexCondTrue( VexCond );

  if ( TrueFalse == -1 )
  {
    viewvexexprboundln( VexCond );
    VasyError( VASY_ERROR_ILLEGAL_USE_OF, "if generate condition" );
  }
  else
  if ( TrueFalse == 1 )
  {
    OldLabel = VasyGenerateLabel;
    sprintf( VasyBuffer, "%s_%s_if", OldLabel, VbhGenerate->LABEL );
    VasyGenerateLabel = namealloc( VasyBuffer );

    for ( ScanGenerate  = VbhGenerate->BEGNR;
          ScanGenerate != (vbgnr_list *)0;
          ScanGenerate  = ScanGenerate->NEXT )
    {
      if ( VbhGenerate->TYPE == VBH_GENERATE_FOR )
      {
        VasyGenerateFor( &VbhGenerate->BEPCS, &VbhGenerate->BEINS, ScanGenerate );
      }
      else
      {
        VasyGenerateIf( &VbhGenerate->BEPCS, &VbhGenerate->BEINS, ScanGenerate );
      }
    }

    VasyGenerateForDupProcess(  VbhFigure, VbhGenerate );
    VasyGenerateForDupInstance( VbhFigure, VbhGenerate );

    VasyGenerateLabel = OldLabel;
  }

  freevexexpr( VexCond );

  if ( IsVasyDebugLevel0() )
  {
    VasyPrintf( stdout, "<-- VasyGenerateIf %s\n", VbhGenerate->LABEL );
  }
}
