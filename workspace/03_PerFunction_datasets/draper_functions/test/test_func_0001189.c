viewrtlfsmtrans( Trans )

  rtlfsmtrans_list *Trans;
{
  rtlfsmasg_list *FsmAsg;

  fprintf( stdout, "\n--> Trans" );

  if ( Trans->FROM != (rtlfsmstate_list *)0 )
  {
    fprintf( stdout, "\n\tFROM     : %s", Trans->FROM->NAME );
  }

  if ( Trans->TO != (rtlfsmstate_list *)0 )
  {
    fprintf( stdout, "\n\tTO       : %s", Trans->TO->NAME );
  }

  fprintf( stdout, "\n\t\tVEX_COND : " );

  viewvexexprbound( Trans->VEX_COND );

  for ( FsmAsg  = Trans->ASSIGN;
        FsmAsg != (rtlfsmasg_list *)0;
        FsmAsg  = FsmAsg->NEXT )
  {
    viewrtlfsmasg( FsmAsg );
  }

  fprintf( stdout, "\n\tFLAGS    : %lx", Trans->FLAGS );
  fprintf( stdout, "\n\tUSER     : %lx", (long)Trans->USER );
}
