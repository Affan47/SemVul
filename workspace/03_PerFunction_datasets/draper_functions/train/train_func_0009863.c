HPDF_Stream_Write  (HPDF_Stream      stream,
                    const HPDF_BYTE  *ptr,
                    HPDF_UINT        size)
{
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Stream_Write\n"));

    if (!(stream->write_fn))
        return HPDF_SetError(stream->error, HPDF_INVALID_OPERATION, 0);


    ret = stream->write_fn(stream, ptr, size);

    if (ret != HPDF_OK)
        return ret;

    stream->size += size;

    return HPDF_OK;
}
