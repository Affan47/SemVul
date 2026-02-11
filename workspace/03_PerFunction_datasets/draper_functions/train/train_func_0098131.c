plc_fillin(plc_state_t *s, int16_t amp[], int len)
{
    int i;
    int pitch_overlap;
    float old_step;
    float new_step;
    float old_weight;
    float new_weight;
    float gain;
    int16_t *orig_amp;
    int orig_len;

    orig_amp = amp;
    orig_len = len;
    if (s->missing_samples == 0)
    {


        normalise_history(s);
        s->pitch = amdf_pitch(PLC_PITCH_MIN, PLC_PITCH_MAX, s->history + PLC_HISTORY_LEN - CORRELATION_SPAN - PLC_PITCH_MIN, CORRELATION_SPAN);

        pitch_overlap = s->pitch >> 2;


        for (i = 0;  i < s->pitch - pitch_overlap;  i++)
            s->pitchbuf[i] = s->history[PLC_HISTORY_LEN - s->pitch + i];

        new_step = 1.0f/pitch_overlap;
        new_weight = new_step;
        for (  ;  i < s->pitch;  i++)
        {
            s->pitchbuf[i] = s->history[PLC_HISTORY_LEN - s->pitch + i]*(1.0f - new_weight) + s->history[PLC_HISTORY_LEN - 2*s->pitch + i]*new_weight;
            new_weight += new_step;
        }


        gain = 1.0f;


        new_step = 1.0f/pitch_overlap;
        old_step = new_step;
        new_weight = new_step;
        old_weight = 1.0f - new_step;
        for (i = 0;  i < pitch_overlap;  i++)
        {
            amp[i] = fsaturate(old_weight*s->history[PLC_HISTORY_LEN - 1 - i] + new_weight*s->pitchbuf[i]);
            new_weight += new_step;
            old_weight -= old_step;
            if (old_weight < 0.0f)
                old_weight = 0.0f;
        }
        s->pitch_offset = i;
    }
    else
    {
        gain = 1.0f - s->missing_samples*ATTENUATION_INCREMENT;
        i = 0;
    }
    for (  ;  gain > 0.0f  &&  i < len;  i++)
    {
        amp[i] = (int16_t) (s->pitchbuf[s->pitch_offset]*gain);
        gain -= ATTENUATION_INCREMENT;
        if (++s->pitch_offset >= s->pitch)
            s->pitch_offset = 0;
    }
    for (  ;  i < len;  i++)
        amp[i] = 0;
    s->missing_samples += orig_len;
    save_history(s, amp, len);
    return len;
}
