nlNormalizeRow(NLdouble weight) {
    NLRowColumn*    af = &nlCurrentContext->af ;
    NLRowColumn*    al = &nlCurrentContext->al ;
    NLuint nf            = af->size ;
    NLuint nl            = al->size ;
    NLuint i ;
    NLdouble norm = 0.0 ;
    for(i=0; i<nf; i++) {
        norm += af->coeff[i].value * af->coeff[i].value ;
    }
    for(i=0; i<nl; i++) {
        norm += al->coeff[i].value * al->coeff[i].value ;
    }
    norm = sqrt(norm) ;
    nlScaleRow(weight / norm) ;
}
