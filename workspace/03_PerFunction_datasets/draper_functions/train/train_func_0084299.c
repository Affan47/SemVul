hattrie_iter_key(hattrie_iter_t* i, size_t* len)
{
    if (hattrie_iter_finished(i)) return NULL;

    uint16_t sublen;
    const char* subkey;

    if (i->has_nil_key) {
        subkey = NULL;
        sublen = 0;
    }
    else subkey = hhash_iter_key(i->i, &sublen);

    if (i->keysize < i->level + sublen + 1) {
        while (i->keysize < i->level + sublen + 1) i->keysize *= 2;
        i->key = realloc(i->key, i->keysize * sizeof(char));
    }

    if (sublen > 0) {
        memcpy(i->key + i->level, subkey, sublen);
    }
    i->key[i->level + sublen] = '\0';

    *len = i->level + sublen;
    return i->key;
}
