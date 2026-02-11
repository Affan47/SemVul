alDeleteAuxiliaryEffectSlots(ALsizei n, const ALuint *effectslots)
{
    ALCcontext *Context;
    ALeffectslot *EffectSlot;
    ALsizei i;

    Context = GetContextRef();
    if(!Context) return;

    if(n < 0)
        alSetError(Context, AL_INVALID_VALUE);
    else
    {

        for(i = 0;i < n;i++)
        {
            if((EffectSlot=LookupEffectSlot(Context, effectslots[i])) == NULL)
            {
                alSetError(Context, AL_INVALID_NAME);
                n = 0;
                break;
            }
            else if(EffectSlot->ref != 0)
            {
                alSetError(Context, AL_INVALID_OPERATION);
                n = 0;
                break;
            }
        }


        for(i = 0;i < n;i++)
        {

            if((EffectSlot=RemoveEffectSlot(Context, effectslots[i])) == NULL)
                continue;
            FreeThunkEntry(EffectSlot->effectslot);

            RemoveEffectSlotArray(Context, EffectSlot);
            ALeffectState_Destroy(EffectSlot->EffectState);

            memset(EffectSlot, 0, sizeof(ALeffectslot));
            free(EffectSlot);
        }
    }

    ALCcontext_DecRef(Context);
}
