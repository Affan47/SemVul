alListener3f(ALenum eParam, ALfloat flValue1, ALfloat flValue2, ALfloat flValue3)
{
    ALCcontext *Context;

    Context = GetContextRef();
    if(!Context) return;

    switch(eParam)
    {
        case AL_POSITION:
            if(isfinite(flValue1) && isfinite(flValue2) && isfinite(flValue3))
            {
                LockContext(Context);
                Context->Listener.Position[0] = flValue1;
                Context->Listener.Position[1] = flValue2;
                Context->Listener.Position[2] = flValue3;
                Context->UpdateSources = AL_TRUE;
                UnlockContext(Context);
            }
            else
                alSetError(Context, AL_INVALID_VALUE);
            break;

        case AL_VELOCITY:
            if(isfinite(flValue1) && isfinite(flValue2) && isfinite(flValue3))
            {
                LockContext(Context);
                Context->Listener.Velocity[0] = flValue1;
                Context->Listener.Velocity[1] = flValue2;
                Context->Listener.Velocity[2] = flValue3;
                Context->UpdateSources = AL_TRUE;
                UnlockContext(Context);
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
