CreateLayer(const char * pszLayerName,
        OGRSpatialReference *poSRS,
        OGRwkbGeometryType eType,
        char ** papszOptions) {
    nLayers++;
    papoLayers = (OGRElasticLayer **) CPLRealloc(papoLayers, nLayers * sizeof (OGRElasticLayer*));
    papoLayers[nLayers - 1] = new OGRElasticLayer(pszName, pszLayerName, this, poSRS, TRUE);

    return papoLayers[nLayers - 1];
}
