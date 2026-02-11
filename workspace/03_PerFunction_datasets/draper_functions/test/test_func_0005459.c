emit() {
    codesequence = new CodeSequence() ;
    codesequence->nregs = nregs ;
    IFNode *n = code ;
    currentAddr = 0 ;
    while (n != NULL) {
       emit (n) ;
       n = n->next ;
    }
    return codesequence ;
}
