LoadSound(char const *Name)
{
    char buf[1024];
    BOOL loop = FALSE;
    Uint8 *buffer;
    Uint32 len;
    SDL_AudioSpec spec;


    if (*Name == '+' || *Name == '-')
        Name++;

    if (*Name == '.') {
        Name++;
        loop = TRUE;
    }

    D(bug("Loading a WAV sample... [%s]", Name));

    sprintf(buf, GAME_DIR "%s", Name);

    if ( SDL_LoadWAV(buf, &spec, &buffer, &len)) {
        struct SoundInfo *s;

        if ( (s = (struct SoundInfo *) calloc(sizeof(struct SoundInfo), 1))) {
            s->Flags = SOUND_FAST;

            if (loop)
                s->Flags |=    SOUND_LOOP;

            s->Volume = 63;
            s->Rate = spec.freq;
            s->Length = len;
            s->SoundData = s->LeftData = buffer;

            D(bug(" length: %d rate: %d\n", len, spec.freq));


#ifdef MACOSX

            if(sound_started && (spec.format != obt.format || spec.freq != obt.freq))
            {
                SDL_AudioCVT  wav_cvt;

                D(bug("Convert sound: original format %x, needed format %x\n",
                    spec.format,obt.format));


                if(SDL_BuildAudioCVT(&wav_cvt,
                        spec.format,spec.channels,spec.freq,
                        obt.format, obt.channels,obt.freq) != -1)
                {

                    if((wav_cvt.buf = malloc(len * wav_cvt.len_mult)) != NULL)
                    {
                        wav_cvt.len = len;
                        memcpy(wav_cvt.buf,buffer,len);


                        SDL_FreeWAV(buffer);


                        SDL_ConvertAudio(&wav_cvt);
                        s->Flags |= SOUND_CONVERTED;
                        s->Length = wav_cvt.len*wav_cvt.len_ratio;
                        s->SoundData = s->LeftData = wav_cvt.buf;
                    }
                }
            }

#else
            if (s->Rate < (samplerate-1000) || s->Rate > (samplerate+1000))
                convert_sound(s);
#endif
            return s;
        }
        SDL_FreeWAV(buffer);
    }

    D(bug("\n*** Unable to load sample!\n"));

    return NULL;
}
