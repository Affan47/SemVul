TestStopMode( paTestData *data )
{
    PaStreamParameters outputParameters;
    PaStream *stream;
    PaError err;

    data->done = 0;
    data->phase = 0.0;
    data->frameCounter = 0;
    data->noteCounter = 0;
    data->repeatCounter = 0;
    data->phase_increment = data->tune[data->noteCounter];

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    outputParameters.device = OUTPUT_DEVICE;
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto error;
    }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = LATENCY_SECONDS;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
              &stream,
              NULL,
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              patestCallback,
              data );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    if( data->stopMode == MODE_FINISH )
    {
        while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
        {


            Pa_Sleep( SLEEP_DUR );
        }
        if( err < 0 ) goto error;
    }
    else
    {
        while( data->repeatCounter < MAX_REPEATS )
        {


            Pa_Sleep( SLEEP_DUR );
        }
    }

    if( data->stopMode == MODE_ABORT )
    {
        printf("Call Pa_AbortStream()\n");
        err = Pa_AbortStream( stream );
    }
    else
    {
        printf("Call Pa_StopStream()\n");
        err = Pa_StopStream( stream );
    }
    if( err != paNoError ) goto error;

    printf("Call Pa_CloseStream()\n"); fflush(stdout);
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    Pa_Terminate();
    printf("Test finished.\n");

    return err;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}
