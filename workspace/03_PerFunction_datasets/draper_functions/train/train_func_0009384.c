PaOssStreamComponent_Configure( PaOssStreamComponent *component, double sampleRate, unsigned long
        framesPerBuffer, StreamMode streamMode, PaOssStreamComponent *master )
{
    PaError result = paNoError;
    int temp, nativeFormat;
    int sr = (int)sampleRate;
    PaSampleFormat availableFormats = 0, hostFormat = 0;
    int chans = component->userChannelCount;
    int frgmt;
    int numBufs;
    int bytesPerBuf;
    unsigned long bufSz;
    unsigned long fragSz;
    audio_buf_info bufInfo;


    if( !master )
    {


        if( framesPerBuffer == paFramesPerBufferUnspecified )
        {
            bufSz = (unsigned long)(component->latency * sampleRate);
            fragSz = bufSz / 4;
        }
        else
        {
            fragSz = framesPerBuffer;
            bufSz = (unsigned long)(component->latency * sampleRate) + fragSz;
        }

        PA_ENSURE( GetAvailableFormats( component, &availableFormats ) );
        hostFormat = PaUtil_SelectClosestAvailableFormat( availableFormats, component->userFormat );


        numBufs = (int)PA_MAX( bufSz / fragSz, 2 );
        bytesPerBuf = PA_MAX( fragSz * Pa_GetSampleSize( hostFormat ) * chans, 16 );


        frgmt = (numBufs << 16) + (CalcHigherLogTwo( bytesPerBuf ) & 0xffff);
        ENSURE_( ioctl( component->fd, SNDCTL_DSP_SETFRAGMENT, &frgmt ), paUnanticipatedHostError );


        PA_ENSURE( Pa2OssFormat( hostFormat, &temp ) );
        nativeFormat = temp;
        ENSURE_( ioctl( component->fd, SNDCTL_DSP_SETFMT, &temp ), paUnanticipatedHostError );
        PA_UNLESS( temp == nativeFormat, paInternalError );


        ENSURE_( ioctl( component->fd, SNDCTL_DSP_CHANNELS, &chans ), paSampleFormatNotSupported );

        PA_UNLESS( chans >= component->userChannelCount, paInvalidChannelCount );


        ENSURE_( ioctl( component->fd, SNDCTL_DSP_SPEED, &sr ), paInvalidSampleRate );


        if( (fabs( sampleRate - sr ) / sampleRate) > 0.01 )
        {
            PA_DEBUG(("%s: Wanted %f, closest sample rate was %d\n", __FUNCTION__, sampleRate, sr ));
            PA_ENSURE( paInvalidSampleRate );
        }

        ENSURE_( ioctl( component->fd, streamMode == StreamMode_In ? SNDCTL_DSP_GETISPACE : SNDCTL_DSP_GETOSPACE, &bufInfo ),
                paUnanticipatedHostError );
        component->numBufs = bufInfo.fragstotal;


        ENSURE_( ioctl( component->fd, SNDCTL_DSP_GETBLKSIZE, &bytesPerBuf ), paUnanticipatedHostError );

        component->hostFrames = bytesPerBuf / Pa_GetSampleSize( hostFormat ) / chans;
        component->hostChannelCount = chans;
        component->hostFormat = hostFormat;
    }
    else
    {
        component->hostFormat = master->hostFormat;
        component->hostFrames = master->hostFrames;
        component->hostChannelCount = master->hostChannelCount;
        component->numBufs = master->numBufs;
    }

    PA_UNLESS( component->buffer = PaUtil_AllocateMemory( PaOssStreamComponent_BufferSize( component ) ),
            paInsufficientMemory );

error:
    return result;
}
