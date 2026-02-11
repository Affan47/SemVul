FindString(WORD wRule, char *ptr)
{

    while(wRule--) {
        while(*ptr++)
        ;
    }
    return ptr;
}
