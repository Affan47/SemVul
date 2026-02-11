ensGvtranscriptvariationadaptorNew(
    EnsPDatabaseadaptor dba)
{
    EnsPBaseadaptor ba = NULL;

    EnsPGvtranscriptvariationadaptor gvtva = NULL;

    if (!dba)
        return NULL;

    if (ajDebugTest("ensGvtranscriptvariationadaptorNew"))
        ajDebug("ensGvtranscriptvariationadaptorNew\n"
                "  dba %p\n",
                dba);

    ba = ensBaseadaptorNew(
        dba,
        gvtranscriptvariationadaptorKTablenames,
        gvtranscriptvariationadaptorKColumnnames,
        gvtranscriptvariationadaptorKLeftjoins,
        gvtranscriptvariationadaptorKDefaultcondition,
        (const char *) NULL,
        &gvtranscriptvariationadaptorFetchAllbyStatement);

    if (!ba)
        return NULL;

    AJNEW0(gvtva);

    gvtva->Adaptor     = ensRegistryGetGvdatabaseadaptor(dba);
    gvtva->Baseadaptor = ba;

    return gvtva;
}
