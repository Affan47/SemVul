oki_adpcm_encode(oki_adpcm_state_t *s,
                     uint8_t oki_data[],
                     const int16_t amp[],
                     int len)
{
    int x;
    int l;
    int n;
    int bytes;
    float z;

    bytes = 0;
    if (s->bit_rate == 32000)
    {
        for (n = 0;  n < len;  n++)
        {
            s->oki_byte = (s->oki_byte << 4) | encode(s, amp[n]);
            if ((s->mark++ & 1))
                oki_data[bytes++] = s->oki_byte;

        }

    }
    else
    {
        n = 0;
        for (;;)
        {

            if (s->phase > 2)
            {
                s->history[s->ptr++] = amp[n];
                s->ptr &= (32 - 1);
                s->phase = 0;
                if (++n >= len)
                    break;

            }

            s->history[s->ptr++] = amp[n];
            s->ptr &= (32 - 1);
            z = 0.0f;
            for (l = 80 - s->phase, x = s->ptr - 1;  l >= 0;  l -= 3, x--)
                z += cutoff_coeffs[l]*s->history[x & (32 - 1)];

            s->oki_byte = (s->oki_byte << 4) | encode(s, (int16_t) (z*3.0f));
            if ((s->mark++ & 1))
                oki_data[bytes++] = s->oki_byte;

            s->phase++;
            if (++n >= len)
                break;

        }

    }

    return  bytes;
}
