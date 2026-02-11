alBuffer3i( ALuint buffer, ALenum eParam, ALint lValue1, ALint lValue2, ALint lValue3)
{
    ALCcontext    *pContext;
    ALCdevice     *device;

    (void)lValue1;
    (void)lValue2;
    (void)lValue3;

    pContext = GetContextRef();
    if(!pContext) return;

    device = pContext->Device;
    if(LookupBuffer(device, buffer) == NULL)
        alSetError(pContext, AL_INVALID_NAME);
    else
    {
        switch(eParam)
        {
        default:
            alSetError(pContext, AL_INVALID_ENUM);
            break;
        }
    }

    ALCcontext_DecRef(pContext);
}
