PlayBackSound(struct SoundInfo * si)
{
    register int i;

    if (no_sound)
        return -1;

    for (i = 0; i < AVAILABLE_CHANNELS; i++) {
        if (!busy[i]) {
            SDL_LockAudio();
            busy[i] = si;

            if (si->Flags & SOUND_DISK)
                fseek((FILE *) si->SoundData, si->FileOffset, SEEK_SET);

            si->Offset = 0;
            SDL_UnlockAudio();
            return i;
        }
    }

    D(bug("All virtual channels busy!\n"));

    return -1;
}
