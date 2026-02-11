archive_compressor_none_finish(struct archive_write *a)
{
    ssize_t block_length;
    ssize_t target_block_length;
    ssize_t bytes_written;
    int ret;
    int ret2;
    struct archive_none *state;

    state = (struct archive_none *)a->compressor.data;
    ret = ret2 = ARCHIVE_OK;
    if (a->client_writer == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
            "No write callback is registered?  "
            "This is probably an internal programming error.");
        return (ARCHIVE_FATAL);
    }


    if (state->next != state->buffer) {
        block_length = state->buffer_size - state->avail;


        target_block_length = block_length;
        if (a->bytes_in_last_block <= 0)

            target_block_length = a->bytes_per_block;
        else

            target_block_length = a->bytes_in_last_block *
                ( (block_length + a->bytes_in_last_block - 1) /
                a->bytes_in_last_block);
        if (target_block_length > a->bytes_per_block)
            target_block_length = a->bytes_per_block;
        if (block_length < target_block_length) {
            memset(state->next, 0,
                target_block_length - block_length);
            block_length = target_block_length;
        }
        bytes_written = (a->client_writer)(&a->archive,
            a->client_data, state->buffer, block_length);
        if (bytes_written <= 0)
            ret = ARCHIVE_FATAL;
        else {
            a->archive.raw_position += bytes_written;
            ret = ARCHIVE_OK;
        }
    }
    if (state->buffer)
        free(state->buffer);
    free(state);
    a->compressor.data = NULL;

    return (ret);
}
