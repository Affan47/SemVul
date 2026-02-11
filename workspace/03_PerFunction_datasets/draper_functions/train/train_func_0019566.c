GDALRegisterTransformDeserializer(const char* pszTransformName,
                                       GDALTransformerFunc pfnTransformerFunc,
                                       GDALTransformDeserializeFunc pfnDeserializeFunc)
{
    TransformDeserializerInfo* psInfo =
        (TransformDeserializerInfo*)CPLMalloc(sizeof(TransformDeserializerInfo));
    psInfo->pszTransformName = CPLStrdup(pszTransformName);
    psInfo->pfnTransformerFunc = pfnTransformerFunc;
    psInfo->pfnDeserializeFunc = pfnDeserializeFunc;

    CPLMutexHolderD(&hDeserializerMutex);
    psListDeserializer = CPLListInsert(psListDeserializer, psInfo, 0);

    return psInfo;
}
