Mdogc (int gctype) {
    void *p;
    long i;
    char n;
    static long prevoti;

    if (Mgcstate == M_GCOFF) {
        Mgcstate = M_GCON;
        p = otarray[0], otarray[0] = otarray[1], otarray[1] = p;
        n = otarea[0], otarea[0] = otarea[1], otarea[1] = n;
        prevoti = oti, oti = otj = 0;
        for (i = 0; i < marki; i++)
            Mmkcurr (markarray[i]);
    }
    if (gctype == M_GCFULL) {
        while (otj != oti) {
            p = otarray[0][otj];
            if (Mhaspointers[M_TYPEOF (p)])
                Tgchelper (p);
            otj++;
        }
    } else {
        for (i = 0; i < gcsteps && otj != oti; i++) {
            p = otarray[0][otj];
            if (Mhaspointers[M_TYPEOF (p)])
                Tgchelper (p);
            otj++;
        }
        if (otj < oti)
            return;
    }
    for (i = 0; i < prevoti; i++) {
        p = otarray[1][i];
        if (p && M_AREAOF (p) == otarea[1]) {
            if (Mhaspointers[M_TYPEOF (p)])
                Tfreehelper (p);
            Mfree (p, (long) ((Mheader_t *) p)->size);
        }
    }
    if (gctype == M_GCINCR) {
        if (numofallocs < NUMOFALLOCS / 2) {
            int t = (gcsteps > GCINCRSTEPS) ? gcsteps >>= 1 : GCINCRSTEPS;
	    t = gcsteps;
            numofallocs = 0;
        }
    }
    if (cbfunc)
        (*cbfunc) ();
    Mgcstate = M_GCOFF;
    Mcouldgc = FALSE;
}
