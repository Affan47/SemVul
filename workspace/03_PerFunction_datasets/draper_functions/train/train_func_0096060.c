putvalue(U32B val, int len) {

    unsigned char buf[4];
    int i;

    for (i=0;i<len;++i,val>>=8) buf[i]=(unsigned char) val&0xff;
    if (write(arcfile,&buf,len)!=len) error(1,ERR_WRITE,arcname);
}
