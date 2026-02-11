MochaCheckViewState( MochaFigure, BddStateSet )

  mochafig_list *MochaFigure;
  bddnode       *BddStateSet;
{
  mochafsm_list   *MochaFsm;
  mochastate_list *MochaState;
  bddnode         *BddState;
  bddnode         *BddReached;
  bddnode         *BddFirst;
  bddnode         *BddFsm;
  bddnode         *BddAssume;
  bddnode         *BddCheck;
  bddnode         *BddOther;
  bddassoc        *BddAssoc;
  bddassoc        *BddRegAssoc;
  int              First;

  setbddlocalcircuit( MochaFigure->BDD_CIRCUIT );

  BddRegAssoc = MochaFigure->BDD_ASSOC_REG;
  BddReached  = MochaFigure->BDD_REACHED_STATE;
  BddFirst    = MochaFigure->BDD_FIRST_STATE;
  BddAssume   = MochaFigure->BDD_ASSUME;

  if ( BddStateSet == BddLocalSystem->ZERO )
  {
    fprintf( stdout, "\t    > state set empty !\n" );
    return ( 0 );
  }

  if ( BddStateSet == BddReached )
  {
    fprintf( stdout, "\t    > all reachable states\n" );
    return ( 1 );
  }

  BddCheck = applybddnode( (bddsystem *)0, ABL_AND, BddStateSet, BddFirst );
  decbddrefext( BddCheck );

  if ( BddCheck == BddFirst ) First = 1;
  else                        First = 0;

  fprintf( stdout, "\t    > states set:\n" );

  while ( BddStateSet != BddLocalSystem->ZERO )
  {
    BddCheck = satisfybddnodeassoc( (bddsystem *)0, BddStateSet, BddRegAssoc );
    BddOther = incbddrefext( BddCheck );

    fprintf( stdout, "\t       " );

    for ( MochaFsm  = MochaFigure->FSM;
          MochaFsm != (mochafsm_list *)0;
          MochaFsm  = MochaFsm->NEXT )
    {
      BddAssoc = MochaFsm->BDD_ASSOC_STATE;
      BddFsm   = existbddnodemissassoc( (bddsystem *)0, BddCheck, BddAssoc );

      BddOther = existbddnodeassoc( (bddsystem *)0,
                                    decbddrefext( BddOther ), BddAssoc );

      for ( MochaState  = MochaFsm->STATE;
            MochaState != (mochastate_list *)0;
            MochaState  = MochaState->NEXT )
      {
        BddState = applybddnode( (bddsystem *)0, ABL_AND,
                                 BddFsm, MochaState->BDD_STATE );
        decbddrefext( BddState );

        if ( BddState == MochaState->BDD_STATE )
        {
          fprintf( stdout, "%s[%s] ", MochaFsm->NAME, MochaState->NAME );
          break;
        }
      }
    }

    if ( ( BddOther != BddLocalSystem->ONE  ) &&
         ( BddOther != BddLocalSystem->ZERO ) )
    {
      MochaCheckViewBddStateNode( BddOther );
      decbddrefext( BddOther );
    }

    if ( BddCheck == BddFirst )
    {
      fprintf( stdout, " (first state)\n" );
    }
    else
    {
      fprintf( stdout, "\n" );
    }

    BddCheck    = applybddnodenot( (bddsystem *)0, decbddrefext( BddCheck ) );
    BddStateSet = applybddnode( (bddsystem *)0, ABL_AND,
                                decbddrefext( BddStateSet ), decbddrefext( BddCheck ) );
  }

  return( First );
}
