appendi (long i) {
    char buf[40];
    int n;

    sprintf (buf, "%ld", i);
    n = strlen (buf) + 1;
    if (sbufi + n > sbufn)
        growsbuf (n);
    strcpy (&sbufp[sbufi], buf);
    sbufi += (n - 1);
}
