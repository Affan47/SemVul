sArray_destruct(sArray *Array){

    int n;

    for (n=0; n<Array->get_dim(Array); n++)
        sSubranges_destruct(Array->m_subranges[n]);
    free(Array->m_subranges);
    free(Array);
    Array=NULL;
}
