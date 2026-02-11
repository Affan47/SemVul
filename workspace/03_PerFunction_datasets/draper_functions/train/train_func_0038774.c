pexpi (int k) {
    int ei0, ei1, ei2, ptok;

    if (lextab[k][0] == 0)
        return pexp5 ();

    ei0 = pexpi (k + 1);
    while ((ptok = getop (Ltok, k)) != -1) {
        ei1 = Cnew (ptok);
        Csetfp (ei1, ei0);
        Lgtok ();
        ei2 = pexpi (k + 1);
        Csetnext (ei0, ei2);
        ei0 = ei1;
    }
    return ei0;
}
