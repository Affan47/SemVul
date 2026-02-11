ApplyOffset(ALsource *Source)
{
    const ALbufferlistitem *BufferList;
    const ALbuffer         *Buffer;
    ALint bufferLen, totalBufferLen;
    ALint buffersPlayed;
    ALint offset;


    offset = GetSampleOffset(Source);


    if(offset == -1)
        return AL_FALSE;


    BufferList = Source->queue;
    totalBufferLen = 0;
    buffersPlayed = 0;

    while(BufferList)
    {
        Buffer = BufferList->buffer;
        bufferLen = Buffer ? Buffer->SampleLen : 0;

        if(bufferLen <= offset-totalBufferLen)
        {

            buffersPlayed++;
        }
        else if(totalBufferLen <= offset)
        {

            Source->BuffersPlayed = buffersPlayed;


            Source->position = offset - totalBufferLen;
            return AL_TRUE;
        }


        totalBufferLen += bufferLen;


        BufferList = BufferList->next;
    }

    return AL_FALSE;
}
