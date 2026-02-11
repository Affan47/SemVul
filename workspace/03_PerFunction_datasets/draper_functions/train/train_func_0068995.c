getPStateLabel(Uint32 idx)
{
    if (createPStateCache())
    {
        DVInstanceCache::ItemStruct *instance = getInstanceStruct();
        if ((instance != NULL) && ((instance->Type == DVPSI_image) || (instance->Type == DVPSI_hardcopyGrayscale)))
        {
            OFListIterator(DVInstanceCache::ItemStruct *) iter = instance->List.begin();
            OFListIterator(DVInstanceCache::ItemStruct *) last = instance->List.end();
            while (iter != last)
            {
                if (idx == 0)
                {
                    DVInstanceCache::ItemStruct *pstate = (*iter);
                    if (pstate != NULL)
                        return pstate->Label.c_str();
                }
                idx--;
                ++iter;
            }
        }
    }
    return NULL;
}
