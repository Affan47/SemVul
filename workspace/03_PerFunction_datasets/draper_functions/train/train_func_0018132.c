RemList (
    Obj                 list)
{
    Int                 pos;
    Obj result;
    pos = LEN_LIST( list ) ;
    if ( pos == 0L ) {
        list = ErrorReturnObj(
                "Remove: <list> must not be empty",
                0L, 0L,
                "you may replace <list> via 'return <list>;'" );
        return RemList(list);
    }
    result = ELM_LIST(list, pos);
    UNB_LIST(list, pos);
    return result;
}
