dictGetSomeKeys(dict *d, dictEntry **des, unsigned int count) {
    unsigned int j;
    unsigned int tables;
    unsigned int stored = 0, maxsizemask;
    unsigned int maxsteps;

    if (dictSize(d) < count) count = dictSize(d);
    maxsteps = count*10;


    for (j = 0; j < count; j++) {
        if (dictIsRehashing(d))
            _dictRehashStep(d);
        else
            break;
    }

    tables = dictIsRehashing(d) ? 2 : 1;
    maxsizemask = d->ht[0].sizemask;
    if (tables > 1 && maxsizemask < d->ht[1].sizemask)
        maxsizemask = d->ht[1].sizemask;


    unsigned int i = random() & maxsizemask;
    unsigned int emptylen = 0;
    while(stored < count && maxsteps--) {
        for (j = 0; j < tables; j++) {


            if (tables == 2 && j == 0 && i < (unsigned int) d->rehashidx) {


                if (i >= d->ht[1].size) i = d->rehashidx;
                continue;
            }
            if (i >= d->ht[j].size) continue;
            dictEntry *he = d->ht[j].table[i];


            if (he == NULL) {
                emptylen++;
                if (emptylen >= 5 && emptylen > count) {
                    i = random() & maxsizemask;
                    emptylen = 0;
                }
            } else {
                emptylen = 0;
                while (he) {


                    *des = he;
                    des++;
                    he = he->next;
                    stored++;
                    if (stored == count) return stored;
                }
            }
        }
        i = (i+1) & maxsizemask;
    }
    return stored;
}
