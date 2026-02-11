alGenAuxiliaryEffectSlots(ALsizei n, ALuint *effectslots)
{
    ALCcontext *Context;

    Context = GetContextRef();
    if(!Context) return;

    if(n < 0 || IsBadWritePtr((void*)effectslots, n * sizeof(ALuint)))
        alSetError(Context, AL_INVALID_VALUE);
    else
    {
        ALenum err;
        ALsizei i;

        err = ResizeEffectSlotArray(Context, n);
        if(err != AL_NO_ERROR)
        {
            alSetError(Context, err);
            n = 0;
        }

        for(i = 0;i < n;i++)
        {
            ALeffectslot *slot = calloc(1, sizeof(ALeffectslot));
            if(!slot || InitEffectSlot(slot) != AL_NO_ERROR)
            {
                free(slot);

                alSetError(Context, AL_OUT_OF_MEMORY);
                alDeleteAuxiliaryEffectSlots(i, effectslots);
                break;
            }

            LockContext(Context);
            err = ResizeEffectSlotArray(Context, 1);
            if(err == AL_NO_ERROR)
                Context->ActiveEffectSlots[Context->ActiveEffectSlotCount++] = slot;
            UnlockContext(Context);
            if(err == AL_NO_ERROR)
                err = NewThunkEntry(&slot->effectslot);
            if(err == AL_NO_ERROR)
                err = InsertUIntMapEntry(&Context->EffectSlotMap, slot->effectslot, slot);
            if(err != AL_NO_ERROR)
            {
                RemoveEffectSlotArray(Context, slot);
                FreeThunkEntry(slot->effectslot);
                ALeffectState_Destroy(slot->EffectState);
                free(slot);

                alSetError(Context, err);
                alDeleteAuxiliaryEffectSlots(i, effectslots);
                break;
            }

            effectslots[i] = slot->effectslot;
        }
    }

    ALCcontext_DecRef(Context);
}
