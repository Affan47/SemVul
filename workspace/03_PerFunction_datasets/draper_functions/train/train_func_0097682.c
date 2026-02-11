copy_bin(BIO *const cl, BIO *const be, LONG cont, LONG *res_bytes, const int no_write)
{
    char        buf[MAXBUF];
    int         res;

    while(cont > L0) {
        if((res = BIO_read(cl, buf, cont > MAXBUF? MAXBUF: cont)) < 0)
            return -1;
        else if(res == 0)
            return -2;
        if(!no_write)
            if(BIO_write(be, buf, res) != res)
                return -3;
        cont -= res;
        if(res_bytes)
            *res_bytes += res;
    }
    if(!no_write)
        if(BIO_flush(be) != 1)
            return -4;
    return 0;
}
