ensBasealignfeatureCalculateAdaptor(const EnsPBasealignfeature baf)
{
    void *Padaptor = NULL;

    if (!baf)
        return NULL;

    switch (baf->Type)
    {
        case ensEBasealignfeatureTypeDNA:

            Padaptor = (void *) baf->Dnaalignfeatureadaptor;

            break;

        case ensEBasealignfeatureTypeProtein:

            Padaptor = (void *) baf->Proteinalignfeatureadaptor;

            break;

        default:

            ajWarn("ensBasealignfeatureCalculateAdaptor got an "
                   "Ensembl Base Align Feature with unexpected type %d.",
                   baf->Type);
    }

    return Padaptor;
}
