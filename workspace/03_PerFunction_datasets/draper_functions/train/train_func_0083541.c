MochaSyfFsmTreatAux( FsmFigure, FbhFigure )

   fsmfig_list    *FsmFigure;
   fbfig_list *FbhFigure;
{
  mochasyfinfo      *MochaSyfInfo;
  fbaux_list        *FbhAux;
  fbrin_list        *FbhRin;
  fsmstate_list     *ScanState;
  mochasyfstate     *ScanSyfState;
  mochasyfregstate  *RegArray;
  int                Index;

  MochaSyfInfo = MOCHA_SYF_INFO( FsmFigure );
  FbhAux  = FbhFigure->BEAUX;
  FbhRin  = FbhFigure->BERIN;

  for ( ScanState  = FsmFigure->STATE;
        ScanState != (fsmstate_list *)0;
        ScanState  = ScanState->NEXT )
  {
    ScanSyfState = MOCHA_SYF_STATE( ScanState );

    FbhAux = fbh_addfbaux( FbhAux, ScanSyfState->CURRENT_NAME,
                           dupablexpr( ScanSyfState->CODE->ABL ), (bddnode *)0, 0 );
    FbhRin = fbh_addfbrin( FbhRin, ScanSyfState->CURRENT_NAME );

    FbhAux = fbh_addfbaux( FbhAux, ScanSyfState->NEXT_NAME,
                           dupablexpr( ScanSyfState->ABL_TRANS ), (bddnode *)0, 0 );
    FbhRin = fbh_addfbrin( FbhRin, ScanSyfState->NEXT_NAME );
  }

  RegArray = MochaSyfInfo->REG_ARRAY;

  for ( Index = MochaSyfInfo->NUMBER_REG - 1; Index >= 0; Index-- )
  {
    FbhAux = fbh_addfbaux( FbhAux, RegArray[ Index ].NAME_IN,
                           dupablexpr( RegArray[ Index ].ABL ), (bddnode *)0, 0 );
    FbhRin = fbh_addfbrin( FbhRin, RegArray[ Index ].NAME_IN );
  }

  FbhFigure->BERIN = FbhRin;
  FbhFigure->BEAUX = FbhAux;
}
