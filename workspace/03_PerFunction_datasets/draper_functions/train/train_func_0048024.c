LoadOperatorData(int operator, genmidi_op_t *data,
                             boolean max_level)
{
    int level;


    level = (data->scale & 0xc0) | (data->level & 0x3f);

    if (max_level)
    {
        level |= 0x3f;
    }

    OPL_WriteRegister(OPL_REGS_LEVEL + operator, level);
    OPL_WriteRegister(OPL_REGS_TREMOLO + operator, data->tremolo);
    OPL_WriteRegister(OPL_REGS_ATTACK + operator, data->attack);
    OPL_WriteRegister(OPL_REGS_SUSTAIN + operator, data->sustain);
    OPL_WriteRegister(OPL_REGS_WAVEFORM + operator, data->waveform);
}
