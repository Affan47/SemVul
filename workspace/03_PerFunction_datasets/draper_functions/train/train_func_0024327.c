ptd_set_chain_references(char *entry,char **entry_tab){
    int counter   = 0;
    long next;
    while (entry){
        entry_tab[counter] = entry;
        counter ++;
        PT_READ_PNTR(entry,next);
        entry = (char *)next;
    }
}
