clear (string cmd) {
    int index = 0 ;
    int bpnum = getNumber (cmd, index) ;
    if (bpnum == 0) {
        for (int i = 0 ; i < breakpoints.size() ; i++) {
            delete breakpoints[i] ;
            breakpoints[i] = NULL ;
        }
    } else {
        if (bpnum > breakpoints.size()) {
            std::cerr << "No such breakpoint\n" ;
        } else {
            delete breakpoints[bpnum - 1] ;
            breakpoints[bpnum - 1] = NULL ;
        }
    }
}
