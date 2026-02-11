ensGvpopulationDel(EnsPGvpopulation *Pgvp)
{
    EnsPGvpopulation subgvp = NULL;
    EnsPGvpopulation pthis = NULL;

    if (!Pgvp)
        return;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 1
    if (ajDebugTest("ensGvpopulationDel"))
    {
        ajDebug("ensGvpopulationDel\n"
                "  *Pgvp %p\n",
                *Pgvp);

        ensGvpopulationTrace(*Pgvp, 1);
    }
#endif

    if (!(pthis = *Pgvp) || --pthis->Use)
    {
        *Pgvp = NULL;

        return;
    }

    ensGvsampleDel(&pthis->Gvsample);

    while (ajListPop(pthis->Subgvpopulations, (void **) &subgvp))
        ensGvpopulationDel(&subgvp);

    ajListFree(&pthis->Subgvpopulations);

    ajMemFree((void **) Pgvp);

    return;
}
