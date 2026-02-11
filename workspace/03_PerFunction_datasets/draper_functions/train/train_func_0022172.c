ensExonCalculateTranscriptCodingEnd(EnsPExon exon,
                                           EnsPTranscript transcript,
                                           EnsPTranslation translation)
{
    ajuint tcend = 0U;

    EnsPExoncoordinates ec = NULL;

    if (!exon)
        return 0U;

    if (!transcript)
        return 0U;

    ec = ensExoncoordinatesNewIni(exon, transcript, translation);

    if (ec)
        tcend = ec->TranscriptCodingEnd;

    ensExoncoordinatesDel(&ec);

    return tcend;
}
