IntrAsssListLevel (
    UInt                level )
{
    Obj                 lists;
    Obj                 poss;
    Obj                 rhss;


    if ( IntrReturning > 0 ) { return; }
    if ( IntrIgnoring  > 0 ) { return; }
    if ( IntrCoding    > 0 ) { CodeAsssListLevel( level ); return; }


    rhss = PopObj();


    poss = PopObj();
    if ( ! IS_POSS_LIST( poss ) ) {
        ErrorQuit(
    "List Assignment: <positions> must be a dense list of positive integers",
            0L, 0L );
    }


    lists = PopObj();


    AsssListLevel( lists, poss, rhss, level );


    PushObj( rhss );
}
