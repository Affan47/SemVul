encode5 (char *s)
{
    unsigned char c = 0;

    while (*s) {
        switch (*s++) {
            case 'a': c |= (1<<1); break;
            case 'b': c |= (1<<2); break;
            case 'c': c |= (1<<4); break;
            case 'd': c |= (1<<3); break;
            case 'e': c |= (1<<0); break;
        }
    }
    return c;
}
