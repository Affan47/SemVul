FuncREM_LIST (
    Obj                 self,
    Obj                 list)

{

    if ( IS_PLIST( list ) ) {
        return RemPlist( list);
    }
    else if ( TNUM_OBJ( list ) < FIRST_EXTERNAL_TNUM ) {
        return RemList( list);
    }
    else {
        return DoOperation1Args( self, list);
    }

}
