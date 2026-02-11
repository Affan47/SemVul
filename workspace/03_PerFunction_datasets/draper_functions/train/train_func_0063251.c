process_modulation_mode(v8_state_t *s, const uint8_t *p)
{
    unsigned int far_end_modulations;


    far_end_modulations = 0;
    if (*p & 0x80)
        far_end_modulations |= V8_MOD_V34HALF;
    if (*p & 0x40)
        far_end_modulations |= V8_MOD_V34;
    if (*p & 0x20)
        far_end_modulations |= V8_MOD_V90;


    if ((*++p & 0x38) == 0x10)
    {
        if (*p & 0x80)
            far_end_modulations |= V8_MOD_V27TER;
        if (*p & 0x40)
            far_end_modulations |= V8_MOD_V29;
        if (*p & 0x04)
            far_end_modulations |= V8_MOD_V17;
        if (*p & 0x02)
            far_end_modulations |= V8_MOD_V22;
        if (*p & 0x01)
            far_end_modulations |= V8_MOD_V32;


        if ((*++p & 0x38) == 0x10)
        {
            if (*p & 0x80)
                far_end_modulations |= V8_MOD_V21;
            if (*p & 0x40)
                far_end_modulations |= V8_MOD_V23HALF;
            if (*p & 0x04)
                far_end_modulations |= V8_MOD_V23;
            if (*p & 0x02)
                far_end_modulations |= V8_MOD_V26BIS;
            if (*p & 0x01)
                far_end_modulations |= V8_MOD_V26TER;
        }
    }
    s->far_end_modulations =
    s->result.modulations = far_end_modulations;
    v8_log_supported_modulations(s, far_end_modulations);
    return ++p;
}
