PaUtil_CopyInput( PaUtilBufferProcessor* bp,
        void **buffer, unsigned long frameCount )
{
    PaUtilChannelDescriptor *hostInputChannels;
    unsigned int framesToCopy;
    unsigned char *destBytePtr;
    void **nonInterleavedDestPtrs;
    unsigned int destSampleStrideSamples;
    unsigned int destChannelStrideBytes;
    unsigned int i;

    hostInputChannels = bp->hostInputChannels[0];
    framesToCopy = PA_MIN_( bp->hostInputFrameCount[0], frameCount );

    if( bp->userInputIsInterleaved )
    {
        destBytePtr = (unsigned char*)*buffer;

        destSampleStrideSamples = bp->inputChannelCount;
        destChannelStrideBytes = bp->bytesPerUserInputSample;

        for( i=0; i<bp->inputChannelCount; ++i )
        {
            bp->inputConverter( destBytePtr, destSampleStrideSamples,
                                hostInputChannels[i].data,
                                hostInputChannels[i].stride,
                                framesToCopy, &bp->ditherGenerator );

            destBytePtr += destChannelStrideBytes;


            hostInputChannels[i].data = ((unsigned char*)hostInputChannels[i].data) +
                    framesToCopy * hostInputChannels[i].stride * bp->bytesPerHostInputSample;
        }


        *buffer = ((unsigned char *)*buffer) +
                framesToCopy * bp->inputChannelCount * bp->bytesPerUserInputSample;
    }
    else
    {


        nonInterleavedDestPtrs = (void**)*buffer;

        destSampleStrideSamples = 1;

        for( i=0; i<bp->inputChannelCount; ++i )
        {
            destBytePtr = (unsigned char*)nonInterleavedDestPtrs[i];

            bp->inputConverter( destBytePtr, destSampleStrideSamples,
                                hostInputChannels[i].data,
                                hostInputChannels[i].stride,
                                framesToCopy, &bp->ditherGenerator );


            destBytePtr += bp->bytesPerUserInputSample * framesToCopy;
            nonInterleavedDestPtrs[i] = destBytePtr;


            hostInputChannels[i].data = ((unsigned char*)hostInputChannels[i].data) +
                    framesToCopy * hostInputChannels[i].stride * bp->bytesPerHostInputSample;
        }
    }

    bp->hostInputFrameCount[0] -= framesToCopy;

    return framesToCopy;
}
