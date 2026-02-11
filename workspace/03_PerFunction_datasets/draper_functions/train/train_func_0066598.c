main(void)
{
    paTestData data;
    int i;
    float simpleTune[] = { NOTE_0, NOTE_1, NOTE_2, NOTE_3, NOTE_4, NOTE_3, NOTE_2, NOTE_1 };

    printf("PortAudio Test: play song and test stopping. ask for %f seconds latency\n", LATENCY_SECONDS );

    for( i=0; i<TABLE_SIZE; i++ )
    {
        data.waveform[i] = (float) (
                               (0.2 * sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. )) +
                               (0.2 * sin( ((double)(3*i)/(double)TABLE_SIZE) * M_PI * 2. )) +
                               (0.1 * sin( ((double)(5*i)/(double)TABLE_SIZE) * M_PI * 2. ))
                           );
    }
    data.waveform[TABLE_SIZE] = data.waveform[0];
    data.tune = &simpleTune[0];
    data.notesPerTune = sizeof(simpleTune) / sizeof(float);

    printf("Test MODE_FINISH - callback returns 1.\n");
    printf("Should hear entire %d note tune repeated twice.\n", data.notesPerTune);
    data.stopMode = MODE_FINISH;
    if( TestStopMode( &data ) != paNoError )
    {
        printf("Test of MODE_FINISH failed!\n");
        goto error;
    }

    printf("Test MODE_STOP - stop when song is done.\n");
    printf("Should hear entire %d note tune repeated twice.\n", data.notesPerTune);
    data.stopMode = MODE_STOP;
    if( TestStopMode( &data ) != paNoError )
    {
        printf("Test of MODE_STOP failed!\n");
        goto error;
    }

    printf("Test MODE_ABORT - abort immediately.\n");
    printf("Should hear last repetition cut short by %f seconds.\n", LATENCY_SECONDS);
    data.stopMode = MODE_ABORT;
    if( TestStopMode( &data ) != paNoError )
    {
        printf("Test of MODE_ABORT failed!\n");
        goto error;
    }

    return 0;

error:
    return 1;
}
