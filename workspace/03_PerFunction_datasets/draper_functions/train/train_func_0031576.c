S_StartSoundAtVolume(void *_origin, int sound_id, int volume)
{
    mobj_t *origin = _origin;
    mobj_t *listener;
    int i;

    listener = GetSoundListener();

    if (sound_id == 0 || snd_MaxVolume == 0)
        return;
    if (origin == NULL)
    {
        origin = listener;
    }

    if (volume == 0)
    {
        return;
    }
    volume = (volume * (snd_MaxVolume + 1) * 8) >> 7;


    for (i = 0; i < snd_Channels; i++)
    {
        if (channel[i].mo == NULL)
        {
            break;
        }
    }
    if (i >= snd_Channels)
    {
        return;
    }
    if (S_sfx[sound_id].lumpnum == 0)
    {
        S_sfx[sound_id].lumpnum = I_GetSfxLumpNum(&S_sfx[sound_id]);
    }


    channel[i].pitch = (byte) (127 - (M_Random() & 3) + (M_Random() & 3));
    channel[i].handle = I_StartSound(&S_sfx[sound_id], i, volume, 128);
    channel[i].mo = origin;
    channel[i].sound_id = sound_id;
    channel[i].priority = 1;
    if (S_sfx[sound_id].usefulness == -1)
    {
        S_sfx[sound_id].usefulness = 1;
    }
    else
    {
        S_sfx[sound_id].usefulness++;
    }
}
