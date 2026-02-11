ReloadLayers()
{
    for(int i=0;i<nLayers;i++)
        delete papoLayers[i];
    CPLFree(papoLayers);
    papoLayers = NULL;
    nLayers = 0;

    Open(pszName, bUpdate);
}
