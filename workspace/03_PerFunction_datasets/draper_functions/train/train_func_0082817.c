ensGvpopulationNewIni(EnsPGvpopulationadaptor gvpa,
                                       ajuint identifier,
                                       EnsPGvsample gvs,
                                       AjPList subpopulations)
{
    AjIList iter = NULL;

    EnsPGvpopulation gvp    = NULL;
    EnsPGvpopulation subgvp = NULL;

    if (!gvs)
        return NULL;

    AJNEW0(gvp);

    gvp->Use        = 1U;
    gvp->Identifier = identifier;
    gvp->Adaptor    = gvpa;
    gvp->Gvsample   = ensGvsampleNewRef(gvs);

    if (ajListGetLength(subpopulations))
    {
        gvp->Subgvpopulations = ajListNew();

        iter = ajListIterNew(subpopulations);

        while (!ajListIterDone(iter))
        {
            subgvp = (EnsPGvpopulation) ajListIterGet(iter);

            ajListPushAppend(gvp->Subgvpopulations,
                             (void *) ensGvpopulationNewRef(subgvp));
        }

        ajListIterDel(&iter);
    }

    return gvp;
}
