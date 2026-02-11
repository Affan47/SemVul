PaOssStream_Stop( PaOssStream *stream, int abort )
{
    PaError result = paNoError;


    int captureErr = 0, playbackErr = 0;
    if( stream->capture )
    {
        if( (captureErr = ioctl( stream->capture->fd, SNDCTL_DSP_POST, 0 )) < 0 )
        {
            PA_DEBUG(( "%s: Failed to stop capture device, error: %d\n", __FUNCTION__, captureErr ));
        }
    }
    if( stream->playback && !stream->sharedDevice )
    {
        if( (playbackErr = ioctl( stream->playback->fd, SNDCTL_DSP_POST, 0 )) < 0 )
        {
            PA_DEBUG(( "%s: Failed to stop playback device, error: %d\n", __FUNCTION__, playbackErr ));
        }
    }

    if( captureErr || playbackErr )
    {
        result = paUnanticipatedHostError;
    }

    return result;
}
