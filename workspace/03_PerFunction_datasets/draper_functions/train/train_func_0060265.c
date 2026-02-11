GrowPRec (
    Obj                 rec,
    UInt                need )
{
    UInt                newsize, want, good;


    want = (2*need+2)*sizeof(Obj);
    if (SIZE_OBJ(rec) >= want) return 0L;


    good = ((5 * LEN_PREC(rec) + 3)/4 + 1) * 2 * sizeof(Obj) + 2;


    newsize = (want < good) ? good : want;


    ResizeBag( rec, newsize );

    return 1L;
}
