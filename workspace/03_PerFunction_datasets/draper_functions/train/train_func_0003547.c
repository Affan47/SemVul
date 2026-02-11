adjust_product(object *item, int adjust, int yield) {
    int nrof = 1;

    if (!yield)
        yield = 1;
    if (adjust <= 0)
        adjust = 1;
    if (item->nrof) {
        nrof = (1.0-1.0/(adjust/10.0+1.0))*(rndm(0, yield-1)+rndm(0, yield-1)+rndm(0, yield-1))+1;
        if (nrof > yield)
            nrof = yield;
        item->nrof = nrof;
    }
}
