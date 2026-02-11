I_free_signatures(struct Signature *S)
{
    int n;
    int i;

    for (i = 0; i < S->nsigs; i++) {
	for (n = 0; n < S->nbands; n++)
	    free(S->sig[i].var[n]);
	free(S->sig[i].var);
	free(S->sig[i].mean);
    }
    I_init_signatures(S, 0);

    return 0;
}
