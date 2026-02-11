GetSpatialRef()

{
    if (CPLGetXMLValue( psLTree, "LayerSRS", NULL ) != NULL)
        return poSRS;

    if (!bHasFullInitialized) FullInitialize();
    if (!poSrcLayer || poDS->GetRecursionDetected()) return NULL;

    return poSRS;
}
