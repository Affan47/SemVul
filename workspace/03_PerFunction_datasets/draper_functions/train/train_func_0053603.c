DedicatedUpdate(ALeffectState *effect, ALCdevice *device, const ALeffectslot *Slot)
{
    ALdedicatedState *state = (ALdedicatedState*)effect;
    const ALfloat *ChannelGain;
    ALfloat Gain;
    ALint pos;
    ALsizei s;

    Gain = Slot->Gain * Slot->effect.Dedicated.Gain;
    for(s = 0;s < MAXCHANNELS;s++)
        state->gains[s] = 0.0f;

    if(Slot->effect.type == AL_EFFECT_DEDICATED_DIALOGUE)
    {
        pos = aluCart2LUTpos(1.0f, 0.0f);
        ChannelGain = device->PanningLUT[pos];

        for(s = 0;s < MAXCHANNELS;s++)
            state->gains[s] = ChannelGain[s] * Gain;
    }
    else if(Slot->effect.type == AL_EFFECT_DEDICATED_LOW_FREQUENCY_EFFECT)
        state->gains[LFE] = Gain;
}
