font_cache_find(const char *name, unsigned char type)
{

    cachefont_t *current;

    ASSERT_RVAL(name != NULL, NULL);

    D_FONT(("font_cache_find(%s, %d) called.\n", NONULL(name), type));


    for (current = font_cache; current; current = current->next) {
        D_FONT((" -> Checking current (%8p), type == %d, name == %s\n", current, current->type, NONULL(current->name)));
        if ((current->type == type) && !strcasecmp(current->name, name)) {
            D_FONT(("    -> Match!\n"));
            return (current);
        }
    }
    D_FONT(("No matches found. =(\n"));
    return ((cachefont_t *) NULL);
}
