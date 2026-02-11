ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigned int num) {
    unsigned char *p = ziplistIndex(zl,index);
    return (p == NULL) ? zl : __ziplistDelete(zl,p,num);
}
