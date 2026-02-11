FrequencyForVoice(opl_voice_t *voice)
{
    genmidi_voice_t *gm_voice;
    unsigned int freq_index;
    unsigned int octave;
    unsigned int sub_index;
    unsigned int note;

    note = voice->note;


    gm_voice = &voice->current_instr->voices[voice->current_instr_voice];

    if ((SHORT(voice->current_instr->flags) & GENMIDI_FLAG_FIXED) == 0)
    {
        note += (signed short) SHORT(gm_voice->base_note_offset);
    }


    if (note > 0x7f)
    {
        note = voice->note;
    }

    freq_index = 64 + 32 * note + voice->channel->bend;


    if (voice->current_instr_voice != 0)
    {
        freq_index += (voice->current_instr->fine_tuning / 2) - 64;
    }


    if (freq_index < 284)
    {
        return frequency_curve[freq_index];
    }

    sub_index = (freq_index - 284) % (12 * 32);
    octave = (freq_index - 284) / (12 * 32);


    if (octave >= 7)
    {
        if (sub_index < 5)
        {
            octave = 7;
        }
        else
        {
            octave = 6;
        }
    }


    return frequency_curve[sub_index + 284] | (octave << 10);
}
