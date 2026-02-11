ProdGF2VecGF2Mat ( Obj vl, Obj vr )
{
    UInt                len;
    UInt                stop;
    UInt                col;
    UInt                i;
    Obj                 prod;
    Obj                 row1;
    UInt *              start;
    UInt *              ptL;
    UInt                mask;


    len = LEN_GF2VEC(vl);
    if (len > LEN_GF2MAT(vr))
      len = LEN_GF2MAT(vr);


    row1 = ELM_GF2MAT( vr, 1 );
    col = LEN_GF2VEC( row1 );
    NEW_GF2VEC( prod, (IS_MUTABLE_OBJ(vl) || IS_MUTABLE_OBJ(row1)) ?
		TYPE_LIST_GF2VEC : TYPE_LIST_GF2VEC_IMM, col );
    SET_LEN_GF2VEC( prod, col );


    start = BLOCKS_GF2VEC(prod);
    ptL   = BLOCKS_GF2VEC(vl);


    for ( i = 1;  i <= len;  ptL++ )  {


        if (*ptL == 0) {
            i += BIPEB;
            continue;
        }


        stop = i + BIPEB - 1;
        if ( len < stop )
            stop = len;
        for ( mask = 1;  i <= stop;  i++, mask <<= 1 ) {


            if ( (*ptL & mask) != 0 ) {
                UInt * ptRR = BLOCKS_GF2VEC(ELM_GF2MAT(vr,i));
		AddGF2VecToGF2Vec(start, ptRR, col);
            }
        }
    }


    return prod;
}
