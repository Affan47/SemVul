CPLHashSetForeach(CPLHashSet* set,
                        CPLHashSetIterEltFunc fnIterFunc,
                        void* user_data)
{
    CPLAssert(set != NULL);
    if (!fnIterFunc) return;

    for(int i=0;i<set->nAllocatedSize;i++)
    {
        CPLList* cur = set->tabList[i];
        while(cur)
        {
            if (fnIterFunc(cur->pData, user_data) == FALSE)
                return;

            cur = cur->psNext;
        }
    }
}
