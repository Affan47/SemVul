needSeparateLoop(Tree sig)
{
    Occurences* o = fOccMarkup.retrieve(sig);
    Type        t = getCertifiedSigType(sig);
    int         c = getSharingCount(sig);
    bool        b;

    int         i;
    Tree        x,y;


    if (o->getMaxDelay()>0) {

        b = true;
    } else if (verySimple(sig) || t->variability()<kSamp) {
        b = false;
    } else if (isSigFixDelay(sig, x, y)) {
        b = false;
    } else if (isProj(sig, &i ,x)) {

        b = true;
    } else if (c > 1) {

        b = true;
    } else {


        b = false;
    }


    return b;
}
