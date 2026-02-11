chk1(packet,len) char *packet; int len; {
    unsigned int x;
    x = chksum(packet,len);
    if (debug) fprintf(db,"chksum=%u\n",x);
    return((((x & 192) >> 6) + x) & 63);
}
