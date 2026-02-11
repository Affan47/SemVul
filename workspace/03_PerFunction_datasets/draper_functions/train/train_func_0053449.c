fs_free_agg_rows(GPtrArray *agg,int vars) {
    for(int i=0;i<agg->len;i++) {
        fs_row *p = g_ptr_array_index(agg,i);
        for (int j=0; j<vars; j++) {
            g_free((gpointer)p[j].name);
            g_free((gpointer)p[j].lex);
            g_free((gpointer)p[j].dt);
            g_free((gpointer)p[j].lang);
        }
        free(p);
    }
    g_ptr_array_free(agg,1);
}
