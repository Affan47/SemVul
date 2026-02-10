nlRowColumnAppend(NLRowColumn* c, NLint index, NLdouble value) {
    if(c->size == c->capacity) {
        nlRowColumnGrow(c) ;
    }
    c->coeff[c->size].index = index ;
    c->coeff[c->size].value = value ;
    c->size++ ;
}
