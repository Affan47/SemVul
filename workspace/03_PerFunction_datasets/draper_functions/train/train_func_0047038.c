lookup(uint32_t addr, int left, int right) {


int         Ai,Bi,Ci,Di;
int         Av,Bv,Cv,Dv;
uint32_t    haddr;

    if ( !rtable ) return(NULL);
    haddr = ntohl(addr);

    if ( right - left <= 1 ) {
        if (rtable[left].network == ( haddr & rtable[left].mask )) {
            return(&rtable[left]);
        }
        return(NULL);
    }
    Ai = left;
    Di = right;
    Bi = (Ai+Di)/2;
    Ci = (Ai+Di)/2 + 1;

    if ( rtable[Bi].network == ( haddr & rtable[Bi].mask ) ) {

        return(&rtable[Bi]);
    } else
    if ( rtable[Bi].network > ( haddr & rtable[Bi].mask ) ) {

        return(lookup(addr, Ai, Bi));
    } else {

        return(lookup(addr, Ci, Di));
    }
}
