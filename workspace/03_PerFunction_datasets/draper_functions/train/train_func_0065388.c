registryCoreStyleDel(
    RegistryPCoreStyle *Prcs)
{
    RegistryPCoreStyle pthis = NULL;

    if (!Prcs)
        return;

#if defined(AJ_DEBUG) && AJ_DEBUG >= 1
    if (ajDebugTest("registryCoreStyleDel"))
    {
        ajDebug("registryCoreStyleDel\n"
                "  *Prcs %p\n",
                *Prcs);

        registryCoreStyleTrace(*Prcs, 1);
    }
#endif

    if (!(pthis = *Prcs))
        return;

    ajStrDel(&pthis->Stableidentifierprefix);


    ensAnalysisadaptorDel(
        &pthis->Analysisadaptor);

    ensAssemblyexceptionadaptorDel(
        &pthis->Assemblyexceptionadaptor);

    ensAssemblyexceptionfeatureadaptorDel(
        &pthis->Assemblyexceptionfeatureadaptor);

    ensAssemblymapperadaptorDel(
        &pthis->Assemblymapperadaptor);

    ensAttributetypeadaptorDel(
        &pthis->Attributetypeadaptor);

    ensCoordsystemadaptorDel(
        &pthis->Coordsystemadaptor);

    ensDensityfeatureadaptorDel(
        &pthis->Densityfeatureadaptor);

    ensDensitytypeadaptorDel(
        &pthis->Densitytypeadaptor);

    ensDitagadaptorDel(
        &pthis->Ditagadaptor);

    ensDitagfeatureadaptorDel(
        &pthis->Ditagfeatureadaptor);

    ensDnaalignfeatureadaptorDel(
        &pthis->Dnaalignfeatureadaptor);

    ensExonadaptorDel(
        &pthis->Exonadaptor);

    ensExternaldatabaseadaptorDel(
        &pthis->Externaldatabaseadaptor);

    ensGeneadaptorDel(
        &pthis->Geneadaptor);

    ensIntronsupportingevidenceadaptorDel(
        &pthis->Intronsupportingevidenceadaptor);

    ensKaryotypebandadaptorDel(
        &pthis->Karyotypebandadaptor);

    ensMarkeradaptorDel(
        &pthis->Markeradaptor);

    ensMarkerfeatureadaptorDel(
        &pthis->Markerfeatureadaptor);

    ensMetainformationadaptorDel(
        &pthis->Metainformationadaptor);

    ensMetacoordinateadaptorDel(
        &pthis->Metacoordinateadaptor);

    ensMiscellaneousfeatureadaptorDel(
        &pthis->Miscellaneousfeatureadaptor);

    ensMiscellaneoussetadaptorDel(
        &pthis->Miscellaneoussetadaptor);

    ensOperonadaptorDel(
        &pthis->Operonadaptor);

    ensOperontranscriptadaptorDel(
        &pthis->Operontranscriptadaptor);

    ensPredictionexonadaptorDel(
        &pthis->Predictionexonadaptor);

    ensPredictiontranscriptadaptorDel(
        &pthis->Predictiontranscriptadaptor);

    ensProteinalignfeatureadaptorDel(
        &pthis->Proteinalignfeatureadaptor);

    ensProteinfeatureadaptorDel(
        &pthis->Proteinfeatureadaptor);

    ensRepeatconsensusadaptorDel(
        &pthis->Repeatconsensusadaptor);

    ensRepeatfeatureadaptorDel(
        &pthis->Repeatfeatureadaptor);

    ensSeqregionadaptorDel(
        &pthis->Seqregionadaptor);

    ensSeqregionsynonymadaptorDel(
        &pthis->Seqregionsynonymadaptor);

    ensSequenceadaptorDel(
        &pthis->Sequenceadaptor);

    ensSimplefeatureadaptorDel(
        &pthis->Simplefeatureadaptor);

    ensSliceadaptorDel(
        &pthis->Sliceadaptor);

    ensTranscriptadaptorDel(
        &pthis->Transcriptadaptor);

    ensTranslationadaptorDel(
        &pthis->Translationadaptor);


    ensDatabaseadaptorDel(
        &pthis->Referenceadaptor);

    ensDatabaseadaptorDel(
        &pthis->Databaseadaptor);

    ajMemFree((void **) Prcs);

    return;
}
