MaxCombinedHeight(void)
{
    intish i;
    intish j;
    floatish mx;
    int bucket;
    floatish value;
    struct chunk* ch;
    floatish *maxima;

    maxima = (floatish*) xmalloc(nsamples * sizeof(floatish));
    for (i = 0; i < nsamples; i++) {
        maxima[ i ] = 0.0;
    }

    for (i = 0; i < nidents; i++) {
        for (ch = identtable[i]->chk; ch; ch = ch->next) {
            for (j = 0; j < ch->nd; j++) {
                bucket = ch->d[j].bucket;
                value  = ch->d[j].value;
		if (bucket >= nsamples)
		    Disaster("bucket out of range");
                maxima[ bucket ] += value;
            }
        }
    }

    for (mx = maxima[ 0 ], i = 0; i < nsamples; i++) {
        if (maxima[ i ] > mx) mx = maxima[ i ];
    }

    free(maxima);
    return mx;
}
