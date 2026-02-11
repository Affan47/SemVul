VhdlWriteStack( ScanState )

  fsmstate_list *ScanState;
{
  fsmstack_list *ScanStack;
  chain_list    *ScanChain;

  for ( ScanChain  = ScanState->STACK;
        ScanChain != (chain_list *)0;
        ScanChain  = ScanChain->NEXT )
  {
    ScanStack = (fsmstack_list *)ScanChain->DATA;

    if ( IsFsmStarStack( ScanStack ) ) continue;

    if ( ScanStack->ABL != (ablexpr    *)0 )
    {
      fprintf( VhdlFile, "      IF ( " );
      viewablexprfile( VhdlFile, ScanStack->ABL, ABL_VIEW_VHDL );
      fprintf( VhdlFile, " )\n      THEN CONTROL <= %s;\n",
               FSM_CTRL_NAME[ (long)ScanStack->CTRL ] );

      if ( ScanStack->CTRL == FSM_CTRL_PUSH )
      {
        fprintf( VhdlFile, "           RETURN_STATE <= %s;\n",
                 vhdlablname( ScanStack->RETURN->NAME ) );
      }
      else
      if ( ScanStack->CTRL == FSM_CTRL_POP )
      {
        fprintf( VhdlFile, "           NEXT_STATE <= STACK_0;\n" );
      }

      fprintf( VhdlFile, "      END IF;\n" );
    }
  }
}
