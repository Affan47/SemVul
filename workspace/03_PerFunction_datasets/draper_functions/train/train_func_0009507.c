createabloper( Oper )

  long Oper;
{
  if ( ( Oper < 0                 ) ||
       ( Oper >= ABL_MAX_OPERATOR ) )
  {
    ablerror( ABL_OPERATOR_ERROR, Oper );
  }

  return( addchain( (ablexpr *)0,
                    (void *)addchain( (ablexpr *)0,
                                      (void *)Oper ) ) );
}
