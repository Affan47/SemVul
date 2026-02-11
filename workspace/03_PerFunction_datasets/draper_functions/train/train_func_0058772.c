init_myers(long max_seq_length) {
    if (!error) {
        naa1 = (int **)ckalloc(MAX_BASETYPES * sizeof (int *) );
        naa2 = (int **)ckalloc(MAX_BASETYPES * sizeof (int *) );
        naas = (int **)ckalloc(MAX_BASETYPES * sizeof (int *) );

        for(int i=0;i<MAX_BASETYPES && !error; i++) {
            naa1[i] = (int *)ckalloc((max_seq_length+1)*sizeof(int));
            naa2[i] = (int *)ckalloc((max_seq_length+1)*sizeof(int));
            naas[i] = (int *)ckalloc((max_seq_length+1)*sizeof(int));
        }
    }
}
