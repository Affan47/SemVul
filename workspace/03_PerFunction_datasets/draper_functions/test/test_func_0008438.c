MakeLower(struct WordList *wl)
{
    unsigned long i;
    FORWL(i, *wl) strlwr(wl->Stack.Data[i]);
    ReHash(wl);
}
