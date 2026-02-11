sys_get_audio_apis(char *buf)
{
    int n = 0;
    strcpy(buf, "{ ");
#ifdef USEAPI_OSS
    sprintf(buf + strlen(buf), "{OSS %d} ", API_OSS); n++;
#endif
#ifdef USEAPI_MMIO
    sprintf(buf + strlen(buf), "{\"standard (MMIO)\" %d} ", API_MMIO); n++;
#endif
#ifdef USEAPI_ALSA
    sprintf(buf + strlen(buf), "{ALSA %d} ", API_ALSA); n++;
#endif
#ifdef USEAPI_PORTAUDIO
#ifdef _WIN32
    sprintf(buf + strlen(buf),
        "{\"ASIO (via portaudio)\" %d} ", API_PORTAUDIO);
#else
#ifdef OSX
    sprintf(buf + strlen(buf),
        "{\"standard (portaudio)\" %d} ", API_PORTAUDIO);
#else
    sprintf(buf + strlen(buf), "{portaudio %d} ", API_PORTAUDIO);
#endif
#endif
     n++;
#endif
#ifdef USEAPI_JACK
    sprintf(buf + strlen(buf), "{jack %d} ", API_JACK); n++;
#endif
#ifdef USEAPI_AUDIOUNIT
    sprintf(buf + strlen(buf), "{AudioUnit %d} ", API_AUDIOUNIT); n++;
#endif
#ifdef USEAPI_ESD
    sprintf(buf + strlen(buf), "{ESD %d} ", API_ESD); n++;
#endif
#ifdef USEAPI_DUMMY
    sprintf(buf + strlen(buf), "{dummy %d} ", API_DUMMY); n++;
#endif
    strcat(buf, "}");

    if (n < 2)
        strcpy(buf, "{}");
}
