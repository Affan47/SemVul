ensIntronsupportingevidenceFetchExons(
    const EnsPIntronsupportingevidence ise,
    EnsPTranscript transcript,
    EnsPExon *Pprevious,
    EnsPExon *Pnext)
{
    ajuint previous = 0U;
    ajuint next     = 0U;

    const AjPList exons = NULL;
    AjIList iter = NULL;

    EnsPExon exon = NULL;

    EnsPFeature efeature = NULL;
    EnsPFeature ifeature = NULL;

    if (!ise)
        return ajFalse;

    if (!transcript)
        return ajFalse;

    if (!Pprevious)
        return ajFalse;

    if (!Pnext)
        return ajFalse;

    *Pprevious = NULL;
    *Pnext    = NULL;

    ifeature = ensIntronsupportingevidenceGetFeature(ise);

    if (ise->Adaptor)
        ensIntronsupportingevidenceadaptorRetrieveExonidentifiers(
            ise->Adaptor,
            ise,
            transcript,
            &previous,
            &next);

    exons = ensTranscriptLoadExons(transcript);

    iter = ajListIterNewread(exons);

    while (!ajListIterDone(iter))
    {
        exon = (EnsPExon) ajListIterGet(iter);

        if (previous && next)
        {


            if (ensExonGetIdentifier(exon) == previous)
                *Pprevious = ensExonNewRef(exon);

            if (ensExonGetIdentifier(exon) == next)
                *Pnext = ensExonNewRef(exon);
        }
        else
        {
            efeature = ensExonGetFeature(exon);

            if (ensFeatureGetStrand(ifeature) >= 0)
            {
                if (ensFeatureGetEnd(efeature) ==
                    (ensFeatureGetStart(ifeature) - 1))
                    *Pprevious = ensExonNewRef(exon);

                if (ensFeatureGetStart(efeature) ==
                    (ensFeatureGetEnd(ifeature) + 1))
                    *Pnext = ensExonNewRef(exon);
            }
            else
            {
                if (ensFeatureGetStart(efeature) ==
                    (ensFeatureGetEnd(ifeature) + 1))
                    *Pprevious = ensExonNewRef(exon);

                if (ensFeatureGetEnd(efeature) ==
                    (ensFeatureGetStart(ifeature) - 1))
                    *Pnext = ensExonNewRef(exon);

            }
        }
    }

    ajListIterDel(&iter);

    return ajTrue;
}
