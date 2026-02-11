FuncREC_NAMES (
    Obj                 self,
    Obj                 rec )
{

    while ( ! IS_PREC_REP(rec) ) {
        rec = ErrorReturnObj(
            "RecNames: <rec> must be a record (not a %s)",
            (Int)TNAM_OBJ(rec), 0L,
            "you can replace <rec> via 'return <rec>;'" );
    }

    return InnerRecNames( rec );
}
