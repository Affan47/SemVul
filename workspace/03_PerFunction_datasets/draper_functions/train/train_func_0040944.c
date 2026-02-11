sound_completion_callback(int chan)
{
    channel_t *sound_channel = sound_channels[chan];
    if (!sound_channel || Mix_Playing(chan))
    {
        gli_strict_warning("sound callback failed");
        return;
    }
    if (!sound_channel->buffered || !sound_channel->decode)
    {
        if (sound_channel->notify)
        {
            gli_event_store(evtype_SoundNotify, 0,
                            sound_channel->resid, sound_channel->notify);
        }
        cleanup_channel(sound_channel);
        sound_channels[chan] = 0;
        return;
    }
    Uint32 soundbytes = Sound_Decode(sound_channel->decode);
    if (!soundbytes)
    {
        sound_channel->loop--;
        if (!sound_channel->loop)
        {
            if (sound_channel->notify)
            {
                gli_event_store(evtype_SoundNotify, 0,
                                sound_channel->resid, sound_channel->notify);
            }
            cleanup_channel(sound_channel);
            sound_channels[chan] = 0;
            return;
        }
        else
        {
            Sound_Rewind(sound_channel->decode);
            soundbytes = Sound_Decode(sound_channel->decode);
        }
    }
    Sound_Sample *sample = sound_channel->decode;
    sound_channel->sample = Mix_QuickLoad_RAW(sample->buffer, soundbytes);
    Mix_ChannelFinished(&sound_completion_callback);
    if (Mix_PlayChannel(sound_channel->sdl_channel,
                        sound_channel->sample,
                        FALSE) >= 0)
    {
        return;
    }
    gli_strict_warning("buffer sound failed");
    gli_strict_warning(Mix_GetError());
    cleanup_channel(sound_channel);
    return;
}
