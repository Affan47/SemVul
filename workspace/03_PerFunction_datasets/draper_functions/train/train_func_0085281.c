FuncOnSets (
    Obj                 self,
    Obj                 set,
    Obj                 elm )
{
    Obj                 img;
    UInt                status;


    while ( !HAS_FILT_LIST(set, FN_IS_SSORT) && ! IsSet( set ) ) {
        set = ErrorReturnObj(
            "OnSets: <set> must be a set (not a %s)",
            (Int)TNAM_OBJ(set), 0L,
            "you can replace <set> via 'return <set>;'" );
    }


    if ( HAS_FILT_LIST( set, FN_IS_EMPTY )) {
      if (IS_MUTABLE_OBJ(set)) {
        img = NEW_PLIST(T_PLIST_EMPTY, 0);
        SET_LEN_PLIST(img,0);
        return img;
      } else {
        return set;
      }
    }


    if ( TNUM_OBJ(elm) == T_PERM2 || TNUM_OBJ(elm) == T_PERM4 ) {
        PLAIN_LIST( set );
        return OnSetsPerm( set, elm );
    }


    img = FuncOnTuples( self, set, elm );


    SortDensePlist( img );


    status = RemoveDupsDensePlist( img );


    switch (status)
      {
      case 0:
        break;

      case 1:
        RetypeBag( img, T_PLIST_DENSE_NHOM_SSORT );

      case 2:
        RetypeBag( img, T_PLIST_HOM_SSORT );

      }


    return img;
}
