sync() {


    if ( pptr() && pptr() > pbase()) {
        if ( flush_buffer() == EOF)
            return -1;
    }
    return 0;
}
