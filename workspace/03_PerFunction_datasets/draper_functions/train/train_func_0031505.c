RemoveDupsDensePlist (
    Obj                 list )
{
    UInt                mutable;
    UInt                homog;
    Int                 len;
    Obj                 v, w;
    UInt                l, i;
    Obj                 fam;


    len = LEN_PLIST( list );
    if ( len == 0 ) { return 0; }


    l = 1;
    v = ELM_PLIST( list, l );
    mutable = IS_MUTABLE_OBJ(v);
    homog = 1;
    fam = FAMILY_OBJ(v);


    for ( i = 2; i <= len; i++ ) {
        w = ELM_PLIST( list, i );
        mutable = (mutable || IS_MUTABLE_OBJ(w));
        if ( ! EQ( v, w ) ) {
            if ( l+1 != i ) {
                SET_ELM_PLIST( list, l+1, w );
                SET_ELM_PLIST( list, i, (Obj)0 );
            }
            l += 1;
            v = w;
            homog = (!mutable && homog && fam == FAMILY_OBJ(w));
        }
    }


    SET_LEN_PLIST( list, l );
    SHRINK_PLIST(  list, l );


    if (!mutable)
      {
        if (!homog)
          SET_FILT_LIST(list, FN_IS_NHOMOG);
        else
          SET_FILT_LIST(list, FN_IS_HOMOG);
        SET_FILT_LIST(list, FN_IS_SSORT);
      }


    if (mutable)
      return 0;
    if (!homog)
      return 1;
    else
      return 2;
}
