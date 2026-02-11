alGetAuxiliaryEffectSlotfv(ALuint effectslot, ALenum param, ALfloat *pflValues)
{
    ALCcontext *Context;

    switch(param)
    {
        case AL_EFFECTSLOT_GAIN:
            alGetAuxiliaryEffectSlotf(effectslot, param, pflValues);
            return;
    }

    Context = GetContextRef();
    if(!Context) return;

    if(LookupEffectSlot(Context, effectslot) != NULL)
    {
        switch(param)
        {
        default:
            alSetError(Context, AL_INVALID_ENUM);
            break;
        }
    }
    else
        alSetError(Context, AL_INVALID_NAME);

    ALCcontext_DecRef(Context);
}
