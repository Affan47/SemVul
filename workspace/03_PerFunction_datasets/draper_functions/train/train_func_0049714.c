alProcessUpdatesSOFT(void)
{
    ALCcontext *Context;

    Context = GetContextRef();
    if(!Context) return;

    if(ExchangeInt(&Context->DeferUpdates, AL_FALSE))
    {
        ALsizei pos;

        LockContext(Context);
        LockUIntMapRead(&Context->SourceMap);
        for(pos = 0;pos < Context->SourceMap.size;pos++)
        {
            ALsource *Source = Context->SourceMap.array[pos].value;
            ALenum new_state;

            if((Source->state == AL_PLAYING || Source->state == AL_PAUSED) &&
               Source->lOffset != -1)
                ApplyOffset(Source);

            new_state = ExchangeInt(&Source->new_state, AL_NONE);
            if(new_state)
                SetSourceState(Source, Context, new_state);
        }
        UnlockUIntMapRead(&Context->SourceMap);
        UnlockContext(Context);
    }

    ALCcontext_DecRef(Context);
}
