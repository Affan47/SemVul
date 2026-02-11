startElementWBCbk(const char *pszName,
                                       const char **ppszAttr)
{
    if (bStopParsing) return;

    nWithoutEventCounter = 0;
    if (strcmp(pszName,"sheet") == 0)
    {
        const char* pszSheetName = GetAttributeValue(ppszAttr, "name", NULL);
        const char* pszSheetId = GetAttributeValue(ppszAttr, "sheetId", NULL);
        if (pszSheetName && pszSheetId)
        {
            int nSheetId = atoi(pszSheetId);
            papoLayers = (OGRLayer**)CPLRealloc(papoLayers, (nLayers + 1) * sizeof(OGRLayer*));
            papoLayers[nLayers++] = new OGRXLSXLayer(this, nSheetId, pszSheetName);
        }
    }
}
