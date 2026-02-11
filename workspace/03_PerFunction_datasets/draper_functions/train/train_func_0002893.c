check_stride(const int incl[],int incllen) {
    int s,i;
    if (incllen > 1) {
        s = incl[1] - incl[0];
    }
    else {
        s = 1;
    }
    if( s < 0 ) {
        return -1;
    }
    for(i=0 ; i < incllen-1 ; i++) {
    	if(incl[i+1] - incl[i] != s) {
            return -1;
        }
    }
    return s;
}
