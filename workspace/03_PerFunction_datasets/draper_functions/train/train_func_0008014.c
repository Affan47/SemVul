mprCreateHashFromWords(cchar *str)
{
    MprHash     *hash;
    char        *word, *next;

    hash = mprCreateHash(0, 0);
    word = stok(sclone(str), ", \t\n\r", &next);
    while (word) {
        mprAddKey(hash, word, word);
        word = stok(NULL, " \t\n\r", &next);
    }
    return hash;
}
