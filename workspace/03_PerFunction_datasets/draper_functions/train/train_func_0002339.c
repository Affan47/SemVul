S_StopSound(mobj_t * origin)
{
    int i;

    for (i = 0; i < snd_Channels; i++)
    {
        if (Channel[i].mo == origin)
        {
            I_StopSound(Channel[i].handle);
            if (S_sfx[Channel[i].sound_id].usefulness > 0)
            {
                S_sfx[Channel[i].sound_id].usefulness--;
            }
            Channel[i].handle = 0;
            Channel[i].mo = NULL;
        }
    }
}
