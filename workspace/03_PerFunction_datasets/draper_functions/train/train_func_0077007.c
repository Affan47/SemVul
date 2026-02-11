primer_print(char *dest,char * source,int size)
{
    char c;
    c = *(source++);
    if (!is_base(c)) return 1;
    while (size){
        while (!is_base(c)) c=*(source++);
        if ( c == 'N' || c == 'n' ) return 1;
        *(dest++) = c;
        size--;
        if (!c) return 1;
        c = 0;
    }
    *dest = 0;
    return 0;
}
