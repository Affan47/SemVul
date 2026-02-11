sSubranges_sort_subranges(sSubranges* Subranges){

    int i,
        j,
        nitem=0;
    sSubrange *Subrange,
        **Subrange_ptr_table;

    Subranges->enumerate(Subranges, sSubranges_sort_subranges_callback, &nitem);
    Subrange_ptr_table=(sSubrange**)calloc(sizeof(sSubrange*),nitem);

    for (i=0,Subrange=Subranges->m_top; Subrange!=NULL; Subrange=Subrange->get_next(Subrange))
        Subrange_ptr_table[i++]=Subrange;

    qsort(Subrange_ptr_table, i, sizeof(sSubrange*),
          (int(*)(const void*, const void*))sSubranges_sort_subranges_fcmp);

    Subrange=Subranges->m_top=Subrange_ptr_table[0];
    for (j=1; j<i; j++){
        Subrange->set_next(Subrange, Subrange_ptr_table[j]);
        Subrange=Subrange_ptr_table[j];
    }
    Subranges->m_last=Subrange;
    Subrange->set_next(Subrange, NULL);

    free(Subrange_ptr_table);
}
