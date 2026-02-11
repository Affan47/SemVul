noise_init_dbov(noise_state_t *s, int seed, float level, int class_of_noise, int quality)
{
    float rms;

    if (s == NULL)
    {
        if ((s = (noise_state_t *) malloc(sizeof(*s))) == NULL)
            return NULL;
    }
    memset(s, 0, sizeof(*s));
    s->rndnum = (uint32_t) seed;
    rms = 32768.0f*powf(10.0f, level/20.0f);
    if (quality < 4)
        s->quality = 4;
    else if (quality > 20)
        s->quality = 20;
    else
        s->quality = quality;
    if (class_of_noise == NOISE_CLASS_HOTH)
    {

        rms *= 1.043f;
    }
    s->rms = (int32_t) (rms*sqrtf(12.0f/s->quality));
    s->class_of_noise = class_of_noise;
    return s;
}
