ReHash(struct WordList *WL)
{
    unsigned long i = 0;

    ClearHash(&WL->Hash);
    FORWL(i, *WL) InsertHash(WL->Stack.Data[i], &WL->Hash);
}
