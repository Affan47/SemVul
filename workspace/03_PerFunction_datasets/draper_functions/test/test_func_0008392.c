super_tone_rx_init(super_tone_rx_state_t *s,
                                                         super_tone_rx_descriptor_t *desc,
                                                         tone_report_func_t callback,
                                                         void *user_data)
{
    int i;

    if (desc == NULL)
        return NULL;
    if (callback == NULL)
        return NULL;
    if (s == NULL)
    {
        if ((s = (super_tone_rx_state_t *) malloc(sizeof(*s) + desc->monitored_frequencies*sizeof(goertzel_state_t))) == NULL)
            return NULL;
    }

    for (i = 0;  i < 11;  i++)
    {
        s->segments[i].f1 = -1;
        s->segments[i].f2 = -1;
        s->segments[i].min_duration = 0;
    }
    s->segment_callback = NULL;
    s->tone_callback = callback;
    s->callback_data = user_data;
    if (desc)
        s->desc = desc;
    s->detected_tone = -1;
    s->energy = 0.0f;
    for (i = 0;  i < desc->monitored_frequencies;  i++)
        goertzel_init(&s->state[i], &s->desc->desc[i]);
    return  s;
}
