PTM_destroy_mem(void){
    int  pos;
    long i;
    int  sum;

    sum = 0;
    for (pos=0;pos<=PTM_MAX_TABLES;pos++) {
        while (PTM.tables[pos]) {
            sum += pos;
            PT_READ_PNTR( ((char *)PTM.tables[pos]),i);
            PTM.tables[pos] = (char *)i;
        }
    }
    arb_assert(sum >= 0);
    return sum;
}
