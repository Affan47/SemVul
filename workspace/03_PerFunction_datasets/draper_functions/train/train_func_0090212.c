oki_adpcm_decode(oki_adpcm_state_t *s,
                                   int16_t amp[],
                                   const uint8_t oki_data[],
                                   int oki_bytes)
{
    int i;
    int x;
    int l;
    int n;
    int samples;
    float z;

#if (_MSC_VER >= 1400)
    __analysis_assume(s->phase >= 0  &&  s->phase <= 4);
#endif
    samples = 0;
    if (s->bit_rate == 32000)
    {
        for (i = 0;  i < oki_bytes;  i++)
        {
            amp[samples++] = decode(s, (oki_data[i] >> 4) & 0xF) << 4;
            amp[samples++] = decode(s, oki_data[i] & 0xF) << 4;
        }

    }
    else
    {
        n = 0;
        for (i = 0;  i < oki_bytes;  )
        {

            if (s->phase)
            {
                s->history[s->ptr++] =
                    decode(s, (n++ & 1)  ?  (oki_data[i++] & 0xF)  :  ((oki_data[i] >> 4) & 0xF)) << 4;
                s->ptr &= (32 - 1);
            }

            z = 0.0f;
            for (l = 80 - 3 + s->phase, x = s->ptr - 1;  l >= 0;  l -= 4, x--)
                z += cutoff_coeffs[l]*s->history[x & (32 - 1)];
            amp[samples++] = (int16_t) (z*4.0f);
            if (++s->phase > 3)
                s->phase = 0;

        }

    }

    return  samples;
}
