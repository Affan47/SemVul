print3Columns( const char* fmt, uint l1, uint l2, uint l3,
                           const char *c1, const char *c2, const char *c3 )
{
    const char *pc1=c1, *pc2=c2, *pc3=c3;
    char *c1buf = (char *)malloc(l1+1);
    char *c2buf = (char *)malloc(l2+1);
    char *c3buf = (char *)malloc(l3+1);
    if (!c1buf) outOfMemory();
    if (!c2buf) outOfMemory();
    if (!c3buf) outOfMemory();

    do
    {
        pc1 = cutToWhiteSpace(pc1, l1, c1buf);
        pc2 = cutToWhiteSpace(pc2, l2, c2buf);
        pc3 = cutToWhiteSpace(pc3, l3, c3buf);
        printf(fmt,
               c1buf[0]!='\0'?c1buf:"",
               c2buf[0]!='\0'?c2buf:"",
               c3buf[0]!='\0'?c3buf:"");
    } while (pc1 || pc2 || pc3);
    free(c1buf);
    free(c2buf);
    free(c3buf);
}
