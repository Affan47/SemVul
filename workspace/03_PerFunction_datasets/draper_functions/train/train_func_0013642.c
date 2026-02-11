CopyString (
    Obj                 list,
    Int                 mut )
{
    Obj                 copy;


    if ( ! IS_MUTABLE_OBJ(list) ) {
        return list;
    }


    if ( mut ) {
        copy = NewBag( TNUM_OBJ(list), SIZE_OBJ(list) );
    }
    else {
        copy = NewBag( IMMUTABLE_TNUM( TNUM_OBJ(list) ), SIZE_OBJ(list) );
    }
    ADDR_OBJ(copy)[0] = ADDR_OBJ(list)[0];


    ADDR_OBJ(list)[0] = copy;
    CHANGED_BAG( list );


    MARK_LIST( list, COPYING );


    memcpy((void*)(ADDR_OBJ(copy)+1), (void*)(ADDR_OBJ(list)+1),
           ((SIZE_OBJ(copy)+sizeof(Obj)-1)/sizeof(Obj)-1) * sizeof(Obj));


    return copy;
}
