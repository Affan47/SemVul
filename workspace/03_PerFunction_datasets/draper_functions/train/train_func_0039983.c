InitSfxModule(boolean use_sfx_prefix)
{
    int i;

    sound_module = NULL;

    for (i=0; sound_modules[i] != NULL; ++i)
    {


        if (SndDeviceInList(snd_sfxdevice,
                            sound_modules[i]->sound_devices,
                            sound_modules[i]->num_sound_devices))
        {


            if (sound_modules[i]->Init(use_sfx_prefix))
            {
                sound_module = sound_modules[i];
                return;
            }
        }
    }
}
