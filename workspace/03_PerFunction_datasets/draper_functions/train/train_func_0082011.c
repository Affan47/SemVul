GDALUnregisterTransformDeserializer(void* pData)
{
    CPLMutexHolderD(&hDeserializerMutex);
    CPLList* psList = psListDeserializer;
    CPLList* psLast = NULL;
    while(psList)
    {
        if (psList->pData == pData)
        {
            TransformDeserializerInfo* psInfo =
                    (TransformDeserializerInfo*)pData;
            CPLFree(psInfo->pszTransformName);
            CPLFree(pData);
            if (psLast)
                psLast->psNext = psList->psNext;
            else
                psListDeserializer = NULL;
            CPLFree(psList);
            break;
        }
        psLast = psList;
        psList = psList->psNext;
    }
}
