ensGeneLoadTranscripts(EnsPGene gene)
{
    EnsPDatabaseadaptor dba = NULL;

    if (!gene)
        return NULL;

    if (gene->Transcripts)
        return gene->Transcripts;

    if (!gene->Adaptor)
    {
        ajDebug("ensGeneLoadTranscripts cannot fetch "
                "Ensembl Transcript objects for an Ensembl Gene without an "
                "Ensembl Gene Adaptor.\n");

        return NULL;
    }

    dba = ensGeneadaptorGetDatabaseadaptor(gene->Adaptor);

    gene->Transcripts = ajListNew();

    ensTranscriptadaptorFetchAllbyGene(
        ensRegistryGetTranscriptadaptor(dba),
        gene,
        gene->Transcripts);

    return gene->Transcripts;
}
