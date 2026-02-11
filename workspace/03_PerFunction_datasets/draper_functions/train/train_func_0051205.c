alGetFilteri(ALuint filter, ALenum param, ALint *piValue)
{
    ALCcontext *Context;
    ALCdevice  *Device;
    ALfilter   *ALFilter;

    Context = GetContextRef();
    if(!Context) return;

    Device = Context->Device;
    if((ALFilter=LookupFilter(Device, filter)) != NULL)
    {
        switch(param)
        {
        case AL_FILTER_TYPE:
            *piValue = ALFilter->type;
            break;

        default:

            ALfilter_GetParami(ALFilter, Context, param, piValue);
            break;
        }
    }
    else
        alSetError(Context, AL_INVALID_NAME);

    ALCcontext_DecRef(Context);
}
