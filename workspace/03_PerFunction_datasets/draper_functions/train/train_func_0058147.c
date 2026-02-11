UpdateDecorrelator(ALfloat density, ALuint frequency, ALverbState *State)
{
    ALuint index;
    ALfloat length;


    for(index = 0;index < 3;index++)
    {
        length = (DECO_FRACTION * aluPow(DECO_MULTIPLIER, (ALfloat)index)) *
                 LATE_LINE_LENGTH[0] * (1.0f + (density * LATE_LINE_MULTIPLIER));
        State->DecoTap[index] = fastf2u(length * frequency);
    }
}
