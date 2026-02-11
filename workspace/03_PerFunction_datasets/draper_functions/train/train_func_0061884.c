expand_rules()
{
    maxrules += 100;
    plhs = (bucket **) REALLOC(plhs, maxrules*sizeof(bucket *));
    if (plhs == 0) no_space();
    rprec = (short *) REALLOC(rprec, maxrules*sizeof(short));
    if (rprec == 0) no_space();
    rassoc = (char *) REALLOC(rassoc, maxrules*sizeof(char));
    if (rassoc == 0) no_space();
}
