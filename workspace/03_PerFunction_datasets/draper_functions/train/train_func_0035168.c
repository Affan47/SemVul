VasyDynFuncScanInstruction( Instruction )

  ptype_list *Instruction;
{
  ptype_list  *ScanPType;
  ptype_list **PrevPType;
  vbifs_list  *ScanIfs;
  vbcas_list  *ScanCase;
  vbcho_list  *ScanChoice;
  vblop_list  *ScanLoop;
  vbfor_list  *ScanFor;
  vbwhi_list  *ScanWhile;
  vbwas_list  *ScanWait;
  vbnxt_list  *ScanNext;
  vbext_list  *ScanExit;
  int          Offset;

  ScanPType = Instruction;
  PrevPType = &Instruction;

  while ( ScanPType != (ptype_list *)0 )
  {
    switch ( ScanPType->TYPE )
    {
      case VBH_BEIFS :

        ScanIfs = (vbifs_list *)ScanPType->DATA;
        ScanIfs->CND      = VasyDynFuncScanVexCond( PrevPType, ScanIfs->CND );
        ScanIfs->CNDTRUE  = VasyDynFuncScanInstruction( ScanIfs->CNDTRUE  );
        ScanIfs->CNDFALSE = VasyDynFuncScanInstruction( ScanIfs->CNDFALSE );

      break;

      case VBH_BECAS :

        ScanCase = (vbcas_list *)ScanPType->DATA;
        ScanCase->VEX = VasyDynFuncScanVexCond( PrevPType, ScanCase->VEX );

        for ( Offset = 0; Offset < ScanCase->SIZE; Offset++ )
        {
          ScanChoice = &ScanCase->CHOICE[ Offset ];
          ScanChoice->INSTRUCTION = VasyDynFuncScanInstruction( ScanChoice->INSTRUCTION );
        }

      break;

      case VBH_BEFOR :

        ScanFor = (vbfor_list *)ScanPType->DATA;
        ScanFor->INSTRUCTION = VasyDynFuncScanInstruction( ScanFor->INSTRUCTION );

        continue;

      break;

      case VBH_BEWHI :

        ScanWhile = (vbwhi_list *)ScanPType->DATA;
        ScanWhile->CND         = VasyDynFuncScanVexCond( PrevPType, ScanWhile->CND );
        ScanWhile->INSTRUCTION = VasyDynFuncScanInstruction( ScanWhile->INSTRUCTION );

      break;

      case VBH_BELOP :

        ScanLoop = (vblop_list *)ScanPType->DATA;
        ScanLoop->INSTRUCTION = VasyDynFuncScanInstruction( ScanLoop->INSTRUCTION );

      break;

      case VBH_BEASG :

        VasyDynFuncScanAsg( PrevPType, ScanPType, 0 );

      break;

      case VBH_BEVAR :

        VasyDynFuncScanAsg( PrevPType, ScanPType, 1 );

      break;

      case VBH_BEWAS :

        ScanWait = (vbwas_list *)ScanPType->DATA;
        ScanWait->CND = VasyDynFuncScanVexCond( PrevPType, ScanWait->CND );

      break;

      case VBH_BENXT :

        ScanNext = (vbnxt_list *)ScanPType->DATA;
        ScanNext->CND = VasyDynFuncScanVexCond( PrevPType, ScanNext->CND );

      break;

      case VBH_BEEXT :

        ScanExit = (vbext_list *)ScanPType->DATA;
        ScanExit->CND = VasyDynFuncScanVexCond( PrevPType, ScanExit->CND );

      break;

      case VBH_BEAGR :

        VasyError( VASY_NOT_YET_IMPLEMENTED_ERROR, "aggregate assignation" );

      break;
    }

    PrevPType = &ScanPType->NEXT;
    ScanPType = ScanPType->NEXT;
  }

  return( Instruction );
}
