alListenerf(ALenum eParam, ALfloat flValue)
{
    ALCcontext *Context;

    Context = GetContextRef();
    if(!Context) return;

    switch(eParam)
    {
        case AL_GAIN:
            if(flValue >= 0.0f && isfinite(flValue))
            {
                Context->Listener.Gain = flValue;
                Context->UpdateSources = AL_TRUE;
            }
            else
                alSetError(Context, AL_INVALID_VALUE);
            break;

        case AL_METERS_PER_UNIT:
            if(flValue > 0.0f && isfinite(flValue))
            {
                Context->Listener.MetersPerUnit = flValue;
                Context->UpdateSources = AL_TRUE;
            }
            else
                alSetError(Context, AL_INVALID_VALUE);
            break;

        default:
            alSetError(Context, AL_INVALID_ENUM);
            break;
    }

    ALCcontext_DecRef(Context);
}
