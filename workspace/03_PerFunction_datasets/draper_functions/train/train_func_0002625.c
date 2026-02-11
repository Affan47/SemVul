GetSpatialRef()

{
    if (HasLayerDefnError())
        return NULL;

    return poSRS;
}
