mkList (ml_state_t *msp, int ngrps, gid gidset[])
{
    ml_val_t    p, w;


    p = LIST_nil;
    while (ngrps-- > 0) {
        WORD_ALLOC (msp, w, (Word_t)(gidset[ngrps]));
	LIST_cons(msp, p, w, p);
    }

    return p;
}
