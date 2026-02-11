HPDF_Stream_Seek  (HPDF_Stream      stream,
                   HPDF_INT         pos,
                   HPDF_WhenceMode  mode)
{
    HPDF_PTRACE((" HPDF_Stream_Seek\n"));

    if (!(stream->seek_fn))
        return HPDF_SetError (stream->error, HPDF_INVALID_OPERATION, 0);

    if (HPDF_Error_GetCode(stream->error) != 0)
        return HPDF_THIS_FUNC_WAS_SKIPPED;

    return stream->seek_fn(stream, pos, mode);
}
