boxaSmoothSequence(BOXA      *boxas,
                   l_float32  factor,
                   l_int32    subflag,
                   l_int32    maxdiff,
                   l_int32    debug)
{
l_int32  n;
BOXA    *boxae, *boxao, *boxalfe, *boxalfo, *boxame, *boxamo, *boxad;

    PROCNAME("boxaSmoothSequence");

    if (!boxas)
        return (BOXA *)ERROR_PTR("boxas not defined", procName, NULL);
    if ((n = boxaGetCount(boxas)) < 4) {
        L_WARNING("need at least 4 boxes; returning copy\n", procName);
        return boxaCopy(boxas, L_COPY);
    }

    boxaSplitEvenOdd(boxas, 1, &boxae, &boxao);
    if (debug) {
        lept_mkdir("smooth");
        boxaWrite("/tmp/smooth/boxae.ba", boxae);
        boxaWrite("/tmp/smooth/boxao.ba", boxao);
    }

    boxalfe = boxaLinearFit(boxae, factor, debug);
    boxalfo = boxaLinearFit(boxao, factor, debug);
    if (debug) {
        boxaWrite("/tmp/smooth/boxalfe.ba", boxalfe);
        boxaWrite("/tmp/smooth/boxalfo.ba", boxalfo);
    }

    boxame = boxaModifyWithBoxa(boxae, boxalfe, subflag, maxdiff);
    boxamo = boxaModifyWithBoxa(boxao, boxalfo, subflag, maxdiff);
    if (debug) {
        boxaWrite("/tmp/smooth/boxame.ba", boxame);
        boxaWrite("/tmp/smooth/boxamo.ba", boxamo);
    }

    boxad = boxaMergeEvenOdd(boxame, boxamo, 1);
    boxaDestroy(&boxae);
    boxaDestroy(&boxao);
    boxaDestroy(&boxalfe);
    boxaDestroy(&boxalfo);
    boxaDestroy(&boxame);
    boxaDestroy(&boxamo);
    return boxad;
}
