calc_L_i(block l, block ldollar, unsigned i) {
    double_block(l, ldollar);
    for ( ; (i&1)==0 ; i>>=1)
        double_block(l,l);
}
