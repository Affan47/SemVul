v29_rx_restart(v29_rx_state_t *s, int bit_rate, int old_train)
{
    int i;

    switch (bit_rate)
    {
    case 9600:
        s->training_cd = 0;
        break;
    case 7200:
        s->training_cd = 2;
        break;
    case 4800:
        s->training_cd = 4;
        break;
    default:
        return -1;
    }
    s->bit_rate = bit_rate;

#if defined(SPANDSP_USE_FIXED_POINT)
    vec_zeroi16(s->rrc_filter, sizeof(s->rrc_filter)/sizeof(s->rrc_filter[0]));
#else
    vec_zerof(s->rrc_filter, sizeof(s->rrc_filter)/sizeof(s->rrc_filter[0]));
#endif
    s->rrc_filter_step = 0;

    s->scramble_reg = 0;
    s->training_scramble_reg = 0x2A;
    s->training_stage = TRAINING_STAGE_SYMBOL_ACQUISITION;
    s->training_count = 0;
    s->signal_present = 0;
#if defined(IAXMODEM_STUFF)
    s->high_sample = 0;
    s->low_samples = 0;
    s->carrier_drop_pending = FALSE;
#endif
    s->old_train = old_train;

    s->carrier_phase = 0;

    power_meter_init(&(s->power), 4);

    s->constellation_state = 0;

    if (s->old_train)
    {
        s->carrier_phase_rate = s->carrier_phase_rate_save;
        s->agc_scaling = s->agc_scaling_save;
        equalizer_restore(s);
    }
    else
    {
        s->carrier_phase_rate = dds_phase_ratef(CARRIER_NOMINAL_FREQ);
#if defined(SPANDSP_USE_FIXED_POINT)
        s->agc_scaling_save = 0;
        s->agc_scaling = (float) FP_FACTOR*32768.0f*0.0017f/RX_PULSESHAPER_GAIN;
#else
        s->agc_scaling_save = 0.0f;
        s->agc_scaling = 0.0017f/RX_PULSESHAPER_GAIN;
#endif
        equalizer_reset(s);
    }
#if defined(SPANDSP_USE_FIXED_POINT)
    s->carrier_track_i = 8000;
    s->carrier_track_p = 8000000;
#else
    s->carrier_track_i = 8000.0f;
    s->carrier_track_p = 8000000.0f;
#endif
    s->last_sample = 0;
    s->eq_skip = 0;


#if defined(SPANDSP_USE_FIXED_POINT)
    for (i = 0;  i < 2;  i++)
    {
        s->symbol_sync_low[i] = 0;
        s->symbol_sync_high[i] = 0;
        s->symbol_sync_dc_filter[i] = 0;
    }
    s->baud_phase = 0;
#else
    for (i = 0;  i < 2;  i++)
    {
        s->symbol_sync_low[i] = 0.0f;
        s->symbol_sync_high[i] = 0.0f;
        s->symbol_sync_dc_filter[i] = 0.0f;
    }
    s->baud_phase = 0.0f;
#endif
    s->baud_half = 0;

    s->total_baud_timing_correction = 0;

    return 0;
}
