playSound(Mix_Chunk *sound, int volume, int loops)
{
    int channel = -1;
    if (sound) {
        channel = Mix_PlayChannel(-1, sound, loops);
        if (-1 == channel) {

            LOG_WARNING(ExInfo("cannot play sound")
                    .addInfo("Mix", Mix_GetError()));
        }
        else {
            Mix_Volume(channel, m_soundVolume * volume / 100);
        }
    }

    return channel;
}
