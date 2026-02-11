CreateBufferWriter (STREAM* stream, const char *name) {
    stream->sflags = STREAM_FLAG_BUFFER;
    stream->u.buffer.length = 128;
    stream->u.buffer.buffer = AllocMemory(stream->u.buffer.length);
    stream->u.buffer.offset = 0;

    if (stream->u.buffer.buffer == NULL)
    {
        HtpMsg(MSG_ERROR, NULL, "unable to allocate stream buffer");
        return FALSE;
    }
    return TRUE;
}
