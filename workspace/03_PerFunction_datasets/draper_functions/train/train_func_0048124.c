FuncPermList (
    Obj                 self,
    Obj                 list )
{
    Obj                 perm;
    UInt2 *             ptPerm2;
    UInt4 *             ptPerm4;
    UInt                degPerm;
    Obj *               ptList;
    UInt2 *             ptTmp2;
    UInt4 *             ptTmp4;
    Int                 i,  k;


    while ( ! IS_SMALL_LIST( list ) ) {
        list = ErrorReturnObj(
            "PermList: <list> must be a list (not a %s)",
            (Int)TNAM_OBJ(list), 0L,
            "you can replace <list> via 'return <list>;'" );
    }
    PLAIN_LIST( list );


    if ( LEN_LIST( list ) <= 65536 ) {

        degPerm = LEN_LIST( list );


        if ( SIZE_OBJ(TmpPerm) < degPerm * sizeof(UInt2) ) {
            ResizeBag( TmpPerm, degPerm * sizeof(UInt2) );
        }


        perm    = NEW_PERM2( degPerm );
        ptPerm2 = ADDR_PERM2(perm);
        ptList  = ADDR_OBJ(list);
        ptTmp2  = ADDR_PERM2(TmpPerm);


        for ( i = 1; i <= degPerm; i++ )
            ptTmp2[i-1] = 0;


        for ( i = 1; i <= degPerm; i++ ) {


            if ( ptList[i] == 0 ) {


		return Fail;
            }
            if ( TNUM_OBJ(ptList[i]) != T_INT ) {


		return Fail;
            }
            k = INT_INTOBJ(ptList[i]);
            if ( k <= 0 || degPerm < k ) {


		return Fail;
            }


            if ( ptTmp2[k-1] != 0 ) {


		return Fail;
            }
            ptTmp2[k-1] = 1;


            ptPerm2[i-1] = k-1;
        }

    }


    else {

        degPerm = LEN_LIST( list );


        if ( SIZE_OBJ(TmpPerm) < degPerm * sizeof(UInt4) ) {
            ResizeBag( TmpPerm, degPerm * sizeof(UInt4) );
        }


        perm    = NEW_PERM4( degPerm );
        ptPerm4 = ADDR_PERM4(perm);
        ptList  = ADDR_OBJ( list);
        ptTmp4  = ADDR_PERM4(TmpPerm);


        for ( i = 1; i <= degPerm; i++ )
            ptTmp4[i-1] = 0;


        for ( i = 1; i <= degPerm; i++ ) {


            if ( ptList[i] == 0 ) {


		return Fail;
            }
            if ( TNUM_OBJ(ptList[i]) != T_INT ) {


		return Fail;
            }
            k = INT_INTOBJ(ptList[i]);
            if ( k <= 0 || degPerm < k ) {


		return Fail;
            }


            if ( ptTmp4[k-1] != 0 ) {


		return Fail;
            }
            ptTmp4[k-1] = 1;


            ptPerm4[i-1] = k-1;
        }

    }


    return perm;
}
