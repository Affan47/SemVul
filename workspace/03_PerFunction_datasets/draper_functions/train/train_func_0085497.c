destroyTokenHash(tEntry **ht)
{
    int i;

    if (ht == NULL)
        return;

    for (i = 0; i < INITSIZE; i++)
        if (ht[i] != NULL)
            destroyEntry(ht[i]);

    free(ht);
}
