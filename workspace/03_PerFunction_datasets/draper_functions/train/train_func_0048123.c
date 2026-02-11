JS_DHashStringKey(JSDHashTable *table, const void *key)
{
    JSDHashNumber h;
    const unsigned char *s;

    h = 0;
    for (s = (const unsigned char *) key; *s != '\0'; s++)
        h = JS_ROTATE_LEFT32(h, 4) ^ *s;
    return h;
}
