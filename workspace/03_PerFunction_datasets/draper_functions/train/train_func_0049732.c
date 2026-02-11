ptd_write_chain_entries(FILE * out, long *ppos, PTM2 * , char ** entry_tab,  int n_entries, int mainapos){
    static char buffer[100];
    int name;
    int rpos;
    int apos;
    int lastname = 0;
    while (n_entries>0){
        char *entry = entry_tab[n_entries-1];
        n_entries --;
        char *rp = entry;
        rp+= sizeof(PT_PNTR);

        PT_READ_NAT(rp,name);
        PT_READ_NAT(rp,rpos);
        PT_READ_NAT(rp,apos);
        if (name < lastname) {
            fprintf(stderr, "Chain Error name order error %i < %i\n",name, lastname);
            return;
        }
        char *wp = buffer;
        wp = PT_WRITE_CHAIN_ENTRY(wp,mainapos,name-lastname,apos,rpos);
        int size = wp -buffer;
        if (1 !=fwrite(buffer,size,1,out) ) {
            fprintf(stderr,"Write Error (Disc Full ?\?\?)\n");
            exit(EXIT_FAILURE);
        }
        *ppos += size;
        PTM_free_mem(entry,rp-entry);
        lastname = name;
    }
}
