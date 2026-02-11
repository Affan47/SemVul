efreet_mime_magic_entry_free(void *data)
{
    Efreet_Mime_Magic_Entry *e = data;

    IF_FREE(e->mask);
    IF_FREE(e->value);
    IF_FREE(e);
}
