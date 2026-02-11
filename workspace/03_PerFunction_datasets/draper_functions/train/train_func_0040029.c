ensGvalleleLoadAllFaileddescriptions(EnsPGvallele gva)
{
    if (!gva)
        return NULL;

    if (gva->Faileddescriptions)
        return gva->Faileddescriptions;

    if (!gva->Adaptor)
    {
        ajDebug("ensGvalleleLoadAllFaileddescriptions cannot retrieve "
                "AJAX String (failed description) objects for an "
                "Ensembl Genetic Variation Allele whithout an "
                "Ensembl Genetic Variation Allele Adaptor.\n");

        return NULL;
    }

    gva->Faileddescriptions = ajListstrNew();

    ensGvalleleadaptorRetrieveAllFaileddescriptions(
        gva->Adaptor,
        gva,
        gva->Faileddescriptions);

    return gva->Faileddescriptions;
}
