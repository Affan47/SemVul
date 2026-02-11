cut_stream_reader_read_from_io_channel (CutStreamReader *stream_reader,
                                        GIOChannel      *channel)
{
    CutStreamReaderPrivate *priv;

    priv = CUT_STREAM_READER_GET_PRIVATE(stream_reader);
    while (!priv->error_emitted) {
        GIOStatus status;
        gboolean eof = FALSE;
        gchar stream[BUFFER_SIZE + 1];
        gsize length = 0;
        GError *error = NULL;

        status = g_io_channel_read_chars(channel, stream, BUFFER_SIZE,
                                         &length, &error);
        if (status == G_IO_STATUS_EOF)
            eof = TRUE;

        if (error) {
            emit_error(stream_reader,
                       CUT_STREAM_READER_ERROR_READ,
                       error, "failed to read stream");
            break;
        }

        if (length <= 0)
            break;

        if (!cut_stream_reader_read(stream_reader, stream, length))
            break;

        if (eof) {
            cut_stream_reader_end_read(stream_reader);
            break;
        }
    }

    return !priv->error_emitted;
}
