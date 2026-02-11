DoAndFilter (
    Obj                 self,
    Obj                 obj )
{
    Obj                 val;
    Obj                 op;


    op = FLAG1_FILT( self );
    val = CALL_1ARGS( op, obj );
    if ( val != True )  return False;


    op = FLAG2_FILT( self );
    val = CALL_1ARGS( op, obj );
    if ( val != True )  return False;


    return True;
}
