TypePlistCyc (
    Obj                 list )
{
    Obj                 kind;
    Int                 ktype;
    Obj                 family;
    Obj                 kinds;


    ktype  = TNUM_OBJ( list );


    family = FAMILY_TYPE( TYPE_OBJ( ELM_PLIST( list, 1 ) ) );


    kinds  = TYPES_LIST_FAM( family );


    kind = ELM0_LIST( kinds, ktype-T_PLIST_CYC+1 );
    if ( kind == 0 ) {
        kind = CALL_2ARGS( TYPE_LIST_HOM,
            family, INTOBJ_INT(ktype-T_PLIST_CYC+1) );
        ASS_LIST( kinds, ktype-T_PLIST_CYC+1, kind );
    }


    return kind;
}
