my_dopoptosub_at(pTHX_ const PERL_CONTEXT* const cxstk, I32 const startingblock) {
    I32 i;

    assert(cxstk);

    for (i = startingblock; i >= 0; i--) {
        const PERL_CONTEXT* const cx = &cxstk[i];
        if(CxTYPE(cx) == CXt_SUB){
            break;
        }
    }
    return i;
}
