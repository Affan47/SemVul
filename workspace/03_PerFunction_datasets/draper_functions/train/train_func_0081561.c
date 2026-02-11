gsm0610_decode(gsm0610_state_t *s, int16_t amp[], const uint8_t code[], int len)
{
    gsm0610_frame_t frame[2];
    int bytes;
    int samples;
    int i;

    samples = 0;
    for (i = 0;  i < len;  i += bytes)
    {
        switch (s->packing)
        {
        default:
        case GSM0610_PACKING_NONE:
            if ((bytes = gsm0610_unpack_none(frame, &code[i])) < 0)
                return 0;
            decode_a_frame(s, &amp[samples], frame);
            samples += GSM0610_FRAME_LEN;
            break;
        case GSM0610_PACKING_WAV49:
            if ((bytes = gsm0610_unpack_wav49(frame, &code[i])) < 0)
                return 0;
            decode_a_frame(s, &amp[samples], frame);
            samples += GSM0610_FRAME_LEN;
            decode_a_frame(s, &amp[samples], frame + 1);
            samples += GSM0610_FRAME_LEN;
            break;
        case GSM0610_PACKING_VOIP:
            if ((bytes = gsm0610_unpack_voip(frame, &code[i])) < 0)
                return 0;
            decode_a_frame(s, &amp[samples], frame);
            samples += GSM0610_FRAME_LEN;
            break;
        }

    }

    return samples;
}
