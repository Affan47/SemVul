ajSeqBamBgzfWrite(AjPSeqBamBgzf fp, const void* data, int length)
{
    const char *input;
    int block_length;
    int bytes_written;
    int copy_length;
    char *buffer;

    if(fp->open_mode != 'w')
    {
        bamReportError(fp, "file not open for writing");
        return -1;
    }

    if(fp->uncompressed_block == NULL)
        fp->uncompressed_block = malloc(fp->uncompressed_block_size);

    input = data;
    block_length = fp->uncompressed_block_size;
    bytes_written = 0;

    while(bytes_written < length)
    {
        copy_length = BAMBGZFMIN(block_length - fp->block_offset,
                                 length - bytes_written);

        buffer = fp->uncompressed_block;
        memcpy(buffer + fp->block_offset, input, copy_length);
        fp->block_offset += copy_length;
        input += copy_length;
        bytes_written += copy_length;

        if(fp->block_offset == block_length)
        {
            if(ajSeqBamBgzfFlush(fp) != 0)
                break;
        }
    }

    return bytes_written;
}
