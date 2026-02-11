SetUpBuffers( PaOssStream *stream, unsigned long framesAvail )
{
    PaError result = paNoError;

    if( stream->capture )
    {
        PaUtil_SetInterleavedInputChannels( &stream->bufferProcessor, 0, stream->capture->buffer,
                stream->capture->hostChannelCount );
        PaUtil_SetInputFrameCount( &stream->bufferProcessor, framesAvail );
    }
    if( stream->playback )
    {
        PaUtil_SetInterleavedOutputChannels( &stream->bufferProcessor, 0, stream->playback->buffer,
                stream->playback->hostChannelCount );
        PaUtil_SetOutputFrameCount( &stream->bufferProcessor, framesAvail );
    }

    return result;
}
