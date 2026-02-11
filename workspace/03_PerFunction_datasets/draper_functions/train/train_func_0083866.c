create_pro_to_bits() const {
    int i;
    int j;
    long *table = (long *)GB_calloc(sizeof(long),256);
    for ( i = 0 ; i < max_aa; i++) {
        j = index_2_spro[i];
        if (j== '.')  {
            table[i] = -1;
            continue;
        }
        j = s2str[j]->index;
        table[i] = 1<<j;
    }
    return table;
}
