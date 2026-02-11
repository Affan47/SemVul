alGetListeneri(ALenum eParam, ALint *plValue)
{
    ALCcontext *Context;

    Context = GetContextRef();
    if(!Context) return;

    if(plValue)
    {
        switch(eParam)
        {
            default:
                alSetError(Context, AL_INVALID_ENUM);
                break;
        }
    }
    else
        alSetError(Context, AL_INVALID_VALUE);

    ALCcontext_DecRef(Context);
}
