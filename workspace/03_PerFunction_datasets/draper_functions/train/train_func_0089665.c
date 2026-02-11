char_sequence_new (const gchar *string)
{
    GSequence *sequence;

    sequence = g_sequence_new(NULL);

    for (; *string != '\0'; string = g_utf8_next_char(string)) {
        g_sequence_append(sequence, GUINT_TO_POINTER(g_utf8_get_char(string)));
    }

    return sequence;
}
