archive_compressor_gzip_write(struct archive_write *a, const void *buff,
    size_t length)
{
    struct private_data *state;
    int ret;

    state = (struct private_data *)a->compressor.data;
    if (a->client_writer == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
            "No write callback is registered?  "
            "This is probably an internal programming error.");
        return (ARCHIVE_FATAL);
    }


    state->crc = crc32(state->crc, (const Bytef *)buff, length);
    state->total_in += length;


    SET_NEXT_IN(state, buff);
    state->stream.avail_in = length;
    if ((ret = drive_compressor(a, state, 0)) != ARCHIVE_OK)
        return (ret);

    a->archive.file_position += length;
    return (ARCHIVE_OK);
}
