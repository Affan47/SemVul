cleanup(void)
{
    int i;

    current_background = -1;


    for (i = 0; i < NUM_WAVES; i++)
    {
        unload_wave(i);
        sounds[i] = NULL;
    }

    for (i = 0; i < NUM_MUSIC; i++)
    {
        unload_background(i);
        music[i] = NULL;
        music_file[i] = "";
    }


    schedule.clear ();


    if (audio_initialized == true)
    {
        Mix_CloseAudio();
        audio_initialized = false;
    }
}
