SetProjection(const char* pszWKTIn)
{
    CPLFree(pszWKT);
    pszWKT = pszWKTIn ? CPLStrdup(pszWKTIn) : CPLStrdup("");
    bProjDirty = TRUE;
    return CE_None;
}
