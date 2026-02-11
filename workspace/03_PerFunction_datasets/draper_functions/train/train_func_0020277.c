write_chunk_size()
{
    unsigned chunk = -1;
    if (ftdi_write_data_get_chunksize(d->ftdi, &chunk) < 0)
        return -1;

    return chunk;
}
