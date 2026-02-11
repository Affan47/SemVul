remove_table(byte *tables, char *tag, uint *numTables)
{

    int i;

    for (i = 0; i < *numTables;) {
        byte *tab = tables + i * 16;

        if (!memcmp(tab, tag, 4)) {
            memmove(tab, tab + 16, 16 * (*numTables - i - 1));
            --*numTables;
        } else
            ++i;
    }
}
