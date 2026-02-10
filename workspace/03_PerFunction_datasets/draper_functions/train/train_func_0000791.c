AsssListCheck (
    Obj                 list,
    Obj                 poss,
    Obj                 rhss )
{
    if ( ! IS_POSS_LIST(poss) ) {
        ErrorQuit(
    "List Assignment: <positions> must be a dense list of positive integers",
            0L, 0L );
    }
    if ( ! IS_DENSE_LIST(rhss) ) {
        ErrorQuit(
            "List Assignment: <rhss> must be a dense list",
            0L, 0L );
    }
    if ( LEN_LIST( poss ) != LEN_LIST( rhss ) ) {
        ErrorQuit(
     "List Assignment: <rhss> must have the same length as <positions> (%d)",
            (Int)LEN_LIST(poss), 0L );
    }
    ASSS_LIST( list, poss, rhss );
}
