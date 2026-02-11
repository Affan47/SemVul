XfsmPlaceState( FsmState, X, Y )

  fsmstate_list *FsmState;
  long           X;
  long           Y;
{
  fsmtrans_list *Trans;
  fsmstate_list *State;
  chain_list    *ScanChain;
  int            Layer;
  int            First;

  if ( FsmState->USER == (void *)0 )
  {
    if ( IsFsmFirstState( FsmState ) ) Layer = XFSM_FIRST_LAYER;
    else
    if ( IsFsmStarState( FsmState ) )  Layer = XFSM_STAR_LAYER;
    else                               Layer = XFSM_STATE_LAYER;

    FsmState->USER = (void *)autallocheap( sizeof( xfsmcoord ) );
    XfsmAddState( FsmState, X, Y, Layer );

    First = 1;
    Y     = Y - 8;

    for ( ScanChain  = FsmState->FROM;
          ScanChain != (chain_list *)0;
          ScanChain  = ScanChain->NEXT )
    {
      Trans = (fsmtrans_list *)( ScanChain->DATA );
      State = Trans->TO;

      if ( ( ! First ) && ( State != FsmState ) )
      {
        if ( State->USER == (void *)0 ) X += 10;
      }

      if ( First )
      {
        First = ( ( State       == FsmState  ) ||
                  ( State->USER != (void *)0 ) );
      }

      X = XfsmPlaceState( State, X, Y - 8 );
      XfsmAddTrans( Trans );
    }
  }

  return( X );
}
