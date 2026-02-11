IsFormatSupported( struct PaUtilHostApiRepresentation *hostApi,
                                  const PaStreamParameters *inputParameters,
                                  const PaStreamParameters *outputParameters,
                                  double sampleRate )
{
    int inputChannelCount, outputChannelCount;
    PaSampleFormat inputSampleFormat, outputSampleFormat;

    if( inputParameters )
    {
        inputChannelCount = inputParameters->channelCount;
        inputSampleFormat = inputParameters->sampleFormat;


        if( inputSampleFormat & paCustomFormat )
            return paSampleFormatNotSupported;


        if( inputParameters->device == paUseHostApiSpecificDeviceSpecification )
            return paInvalidDevice;


        if( inputChannelCount > hostApi->deviceInfos[ inputParameters->device ]->maxInputChannels )
            return paInvalidChannelCount;


        if( inputParameters->hostApiSpecificStreamInfo )
            return paIncompatibleHostApiSpecificStreamInfo;
    }
    else
    {
        inputChannelCount = 0;
    }

    if( outputParameters )
    {
        outputChannelCount = outputParameters->channelCount;
        outputSampleFormat = outputParameters->sampleFormat;


        if( outputSampleFormat & paCustomFormat )
            return paSampleFormatNotSupported;


        if( outputParameters->device == paUseHostApiSpecificDeviceSpecification )
            return paInvalidDevice;


        if( outputChannelCount > hostApi->deviceInfos[ outputParameters->device ]->maxOutputChannels )
            return paInvalidChannelCount;


        if( outputParameters->hostApiSpecificStreamInfo )
            return paIncompatibleHostApiSpecificStreamInfo;
    }
    else
    {
        outputChannelCount = 0;
    }


    (void) sampleRate;

    return paFormatIsSupported;
}
