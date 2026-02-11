getIfaceBySocket(int fd) {
    SPtr<TIfaceIface> ptr;
    IfaceLst.first();
    while ( ptr = IfaceLst.get() ) {
        if ( ptr->getSocketByFD(fd) )
            return ptr;
    }
    return 0;
}
