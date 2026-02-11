NewStream(
        FCGX_Request *reqDataPtr, int bufflen, int isReader, int streamType)
{


    FCGX_Stream *stream = (FCGX_Stream *)Malloc(sizeof(FCGX_Stream));
    FCGX_Stream_Data *data = (FCGX_Stream_Data *)Malloc(sizeof(FCGX_Stream_Data));
    data->reqDataPtr = reqDataPtr;
    bufflen = AlignInt8(min(max(bufflen, 32), FCGI_MAX_LENGTH + 1));
    data->bufflen = bufflen;
    data->mBuff = (unsigned char *)Malloc(bufflen);
    data->buff = AlignPtr8(data->mBuff);
    if(data->buff != data->mBuff) {
        data->bufflen -= 8;
    }
    if(isReader) {
        data->buffStop = data->buff;
    } else {
        data->buffStop = data->buff + data->bufflen;
    }
    data->type = streamType;
    data->eorStop = FALSE;
    data->skip = FALSE;
    data->contentLen = 0;
    data->paddingLen = 0;
    data->isAnythingWritten = FALSE;
    data->rawWrite = FALSE;

    stream->data = data;
    stream->isReader = isReader;
    stream->isClosed = FALSE;
    stream->wasFCloseCalled = FALSE;
    stream->FCGI_errno = 0;
    if(isReader) {
        stream->fillBuffProc = FillBuffProc;
        stream->emptyBuffProc = NULL;
        stream->rdNext = data->buff;
        stream->stop = stream->rdNext;
        stream->stopUnget = data->buff;
        stream->wrNext = stream->stop;
    } else {
        stream->fillBuffProc = NULL;
        stream->emptyBuffProc = EmptyBuffProc;
        stream->wrNext = data->buff + sizeof(FCGI_Header);
        stream->stop = data->buffStop;
        stream->stopUnget = NULL;
        stream->rdNext = stream->stop;
    }
    return stream;
}
