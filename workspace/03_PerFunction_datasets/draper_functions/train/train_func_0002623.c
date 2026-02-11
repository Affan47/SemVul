FuncPrintExecutingStatement(Obj self, Obj context)
{
  Obj currLVars = CurrLVars;
  Expr call;
  if (context == BottomLVars)
    return (Obj) 0;
  SWITCH_TO_OLD_LVARS(context);
  call = BRK_CALL_TO();
  if ( call == 0 ) {
    Pr( "<compiled or corrupted statement> ", 0L, 0L );
  }
#if T_PROCCALL_0ARGS
    else if ( FIRST_STAT_TNUM <= TNUM_STAT(call)
              && TNUM_STAT(call)  <= LAST_STAT_TNUM ) {
#else
     else if ( TNUM_STAT(call)  <= LAST_STAT_TNUM ) {
#endif
      PrintStat( call );
    }
    else if ( FIRST_EXPR_TNUM <= TNUM_EXPR(call)
              && TNUM_EXPR(call)  <= LAST_EXPR_TNUM ) {
      PrintExpr( call );
    }
    SWITCH_TO_OLD_LVARS( currLVars );
    return (Obj) 0;
}
