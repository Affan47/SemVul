getvalue(int len) {

    unsigned char buf[4];
    U32B val;
    int i;

    if (read(arcfile,buf,len)!=len) error(1,ERR_READ,arcname);
    for (val=i=0;i<len;++i) val|=(U32B)buf[i]<<(i<<3);
    return val;
}
