associate_string (Tuple * tuple, int field, const char *
 customfield, const unsigned char * data, int size)
{
    char * text = decode_text_frame (data, size);

    if (text == NULL || ! text[0])
    {
        g_free (text);
        return;
    }

    if (customfield != NULL)
        TAGDBG ("Custom field %s = %s.\n", customfield, text);
    else
        TAGDBG ("Field %i = %s.\n", field, text);

    tuple_set_str (tuple, field, customfield, text);
    g_free (text);
}
