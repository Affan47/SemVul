FCGX_FFlush(FCGX_Stream *stream)
{
    if(stream->isClosed || stream->isReader)
        return 0;
    stream->emptyBuffProc(stream, FALSE);
    return (stream->isClosed) ? -1 : 0;
}
