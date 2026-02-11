FvhFbhTreatWhen( FbhFigure,  FsmFigure,   ScanCase,
                      PStateFrom, StateTo,     Return,
                      PControl,   Equation )

  fbfig_list  *FbhFigure;
  fsmfig_list     *FsmFigure;
  fbcas_list  *ScanCase;
  fsmstate_list  **PStateFrom;
  fsmstate_list   *StateTo;
  fsmstate_list   *Return;
  int             *PControl;
  ablexpr         *Equation;
{
  fbtyp_list *ScanType;
  int         Index;
  char       *ChoiceValue;

  if ( FvhTreatMainProcess )
  {
    if ( Equation != (ablexpr    *)0 )
    {
      FvhWhenCondition = 1;
    }
  }


  ScanType = (fbtyp_list *)(FbhFigure->BETYP + ScanCase->TYPE - 1);

  if ( ScanType == FvhStateType )
  {
    if ( ( ABL_ATOM( ScanCase->ABL )                              ) &&
         ( ABL_ATOM_VALUE( ScanCase->ABL ) == FvhCurrentStateName ) )
    {
      if ( *PStateFrom == (fsmstate_list *)0 )
      {
        if ( ! FvhTreatMainProcess )
        {
          fvherror( FVH_ERROR_IN_CLOCK_PROCESS, FvhCurrentStateName, ScanCase->LINE_NUM );
        }


        for ( Index = 0; Index < ScanCase->SIZE; Index++ )
        {
          ChoiceValue = ScanCase->CHOICE[ Index ].VALUE;

          if ( ChoiceValue == FvhOthersKeyword ) continue;

          *PStateFrom = searchfsmstate( FsmFigure, ChoiceValue );

          FvhFbhTreatInstruction( FbhFigure, FsmFigure,
                                  ScanCase->CHOICE[ Index ].INSTRUCTION,
                                 *PStateFrom, StateTo, Return,
                                 *PControl, Equation );
        }
      }
      else
      {
        fvherror( FVH_ERROR_ILLEGAL_CASE, ScanType->NAME, ScanCase->LINE_NUM );
      }
    }
    else
    {
      fvherror( FVH_ERROR_ILLEGAL_STATE,
                ABL_ATOM_VALUE( ScanCase->ABL ), ScanCase->LINE_NUM );
    }
  }
  else
  if ( ScanType == FvhControlType )
  {
    if ( ( ABL_ATOM( ScanCase->ABL )                         ) &&
         ( ABL_ATOM_VALUE( ScanCase->ABL ) == FvhControlName ) )
    {
      if ( *PControl == -1 )
      {
        if ( FvhTreatMainProcess )
        {
          fvherror( FVH_ERROR_IN_MAIN_PROCESS, FvhControlName, ScanCase->LINE_NUM );
        }


        for ( Index = 0; Index < ScanCase->SIZE; Index++ )
        {
          ChoiceValue = ScanCase->CHOICE[ Index ].VALUE;

          if ( ChoiceValue == FvhOthersKeyword ) continue;

          *PControl = FvhFbhGetControl( ChoiceValue );

          FvhTreatStackControl = 1;

          FvhFbhTreatInstruction( FbhFigure, FsmFigure,
                                  ScanCase->CHOICE[ Index ].INSTRUCTION,
                                 *PStateFrom, StateTo, Return,
                                 *PControl, Equation );
        }
      }
      else
      {
        fvherror( FVH_ERROR_ILLEGAL_CASE, ScanType->NAME, ScanCase->LINE_NUM );
      }
    }
    else
    {
      fvherror( FVH_ERROR_ILLEGAL_CONTROL,
                ABL_ATOM_VALUE( ScanCase->ABL ), ScanCase->LINE_NUM );
    }
  }
  else
  {
    fvherror( FVH_ERROR_ILLEGAL_CASE, ScanType->NAME, ScanCase->LINE_NUM );
  }
}
