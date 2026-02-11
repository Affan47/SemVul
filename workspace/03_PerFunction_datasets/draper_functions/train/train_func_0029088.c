gnc_is_our_xml_file(const char *filename, gboolean *with_encoding)
{
    FILE *f = NULL;
    char first_chunk[256];
    ssize_t num_read;

    g_return_val_if_fail(filename, GNC_BOOK_NOT_OURS);

    f = g_fopen(filename, "r");
    if (f == NULL)
    {
        return GNC_BOOK_NOT_OURS;
    }

    num_read = fread(first_chunk, sizeof(char), sizeof(first_chunk) - 1, f);
    fclose(f);

    if (num_read == 0)
    {
        return GNC_BOOK_NOT_OURS;
    }

    first_chunk[num_read] = '\0';

    return gnc_is_our_first_xml_chunk(first_chunk, with_encoding);
}
