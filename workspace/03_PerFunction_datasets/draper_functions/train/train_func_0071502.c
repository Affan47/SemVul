ensExonadaptorNew(
    EnsPDatabaseadaptor dba)
{
    EnsPExonadaptor ea = NULL;

    if (!dba)
        return NULL;

    AJNEW0(ea);

    ea->Exonadaptor = ensFeatureadaptorNew(
        dba,
        exonadaptorKTablenames,
        exonadaptorKColumnnames,
        (const EnsPBaseadaptorLeftjoin) NULL,
        (const char *) NULL,
        (const char *) NULL,
        &exonadaptorFetchAllbyStatement,
        (void *(*)(const void *)) NULL,
        (void *(*)(void *)) &ensExonNewRef,
        (AjBool (*)(const void *)) NULL,
        (void (*)(void **)) &ensExonDel,
        (size_t (*)(const void *)) &ensExonCalculateMemsize,
        (EnsPFeature (*)(const void *)) &ensExonGetFeature,
        "Exon");

    ea->Exontranscriptadaptor = ensFeatureadaptorNew(
        dba,
        exontranscriptadaptorKTablenames,
        exonadaptorKColumnnames,
        (const EnsPBaseadaptorLeftjoin) NULL,
        exontranscriptadaptorKDefaultcondition,
        exontranscriptadaptorKFinalcondition,
        &exonadaptorFetchAllbyStatement,
        (void *(*)(const void *)) NULL,
        (void *(*)(void *)) &ensExonNewRef,
        (AjBool (*)(const void *)) NULL,
        (void (*)(void **)) &ensExonDel,
        (size_t (*)(const void *)) &ensExonCalculateMemsize,
        (EnsPFeature (*)(const void *)) &ensExonGetFeature,
        "Exontranscript");

    return ea;
}
