_ghwp_file_v3_parse_styles (GHWPDocument *doc)
{
    g_return_if_fail (doc != NULL);
    guint16 n_styles;
    guint8 *buffer = NULL;
    gsize bytes_read;
    GInputStream *stream = GHWP_FILE_V3 (doc->file)->priv->stream;
    g_input_stream_read_all (stream, &n_styles, 2, &bytes_read, NULL, NULL);
    buffer = g_malloc (n_styles * (20 + 31 + 187));
    g_input_stream_read_all (stream, buffer, n_styles * (20 + 31 + 187), &bytes_read, NULL, NULL);
    g_free (buffer);
}
