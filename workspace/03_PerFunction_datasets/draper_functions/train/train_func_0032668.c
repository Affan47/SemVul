QueryDirection( const char *deviceName, StreamMode mode, double *defaultSampleRate, int *maxChannelCount,
        double *defaultLowLatency, double *defaultHighLatency )
{
    PaError result = paNoError;
    int numChannels, maxNumChannels;
    int busy = 0;
    int devHandle = -1;
    int sr;
    *maxChannelCount = 0;

    if ( (devHandle = open( deviceName, (mode == StreamMode_In ? O_RDONLY : O_WRONLY) | O_NONBLOCK ))  < 0 )
    {
        if( errno == EBUSY || errno == EAGAIN )
        {
            PA_DEBUG(( "%s: Device %s busy\n", __FUNCTION__, deviceName ));
        }
        else
        {

            if( errno != ENOENT )
            {
                PA_DEBUG(( "%s: Can't access device %s: %s\n", __FUNCTION__, deviceName, strerror( errno ) ));
            }
        }

        return paDeviceUnavailable;
    }


    maxNumChannels = 0;
    for( numChannels = 1; numChannels <= 16; numChannels++ )
    {
        int temp = numChannels;
        if( ioctl( devHandle, SNDCTL_DSP_CHANNELS, &temp ) < 0 )
        {
            busy = EAGAIN == errno || EBUSY == errno;

            if( maxNumChannels >= 2 )
                break;
        }
        else
        {


            if( (numChannels > 2) && (temp != numChannels) )
                break;
            if( temp > maxNumChannels )
                maxNumChannels = temp;
        }
    }


    if( 0 == maxNumChannels && busy )
    {
        result = paDeviceUnavailable;
        goto error;
    }


    if( maxNumChannels < 1 )
    {
        int stereo = 1;
        if( ioctl( devHandle, SNDCTL_DSP_STEREO, &stereo ) < 0 )
        {
            maxNumChannels = 1;
        }
        else
        {
            maxNumChannels = (stereo) ? 2 : 1;
        }
        PA_DEBUG(( "%s: use SNDCTL_DSP_STEREO, maxNumChannels = %d\n", __FUNCTION__, maxNumChannels ));
    }


    {

        int temp = PA_MIN( maxNumChannels, 2 );
        ENSURE_( ioctl( devHandle, SNDCTL_DSP_CHANNELS, &temp ), paUnanticipatedHostError );
    }


    if( *defaultSampleRate < 0 )
    {
        sr = 44100;
        ENSURE_( ioctl( devHandle, SNDCTL_DSP_SPEED, &sr ), paUnanticipatedHostError );

        *defaultSampleRate = sr;
    }

    *maxChannelCount = maxNumChannels;

    *defaultLowLatency = 512. / *defaultSampleRate;
    *defaultHighLatency = 2048. / *defaultSampleRate;

error:
    if( devHandle >= 0 )
        close( devHandle );

    return result;
}
