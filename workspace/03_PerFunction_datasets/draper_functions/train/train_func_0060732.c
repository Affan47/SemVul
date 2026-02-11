ensSliceFetchSequenceSubSeq(EnsPSlice slice,
                                   ajint start,
                                   ajint end,
                                   ajint strand,
                                   AjPSeq *Psequence)
{
    ajint srstart  = 0;
    ajint srend    = 0;
    ajint srstrand = 0;

    AjPStr name     = NULL;
    AjPStr sequence = NULL;

    if (!slice)
        return ajFalse;

    if (!strand)
        strand = 1;

    if (!Psequence)
        return ajFalse;


    if (slice->Strand >= 0)
    {
        srstart = slice->Start + start - 1;
        srend   = slice->Start + end   - 1;
    }
    else
    {
        srstart = slice->End - end   + 1;
        srend   = slice->End - start + 1;
    }

    srstrand = slice->Strand * strand;

    name = ajFmtStr("%S:%S:%S:%d:%d:%d",
                    ensSliceGetCoordsystemName(slice),
                    ensSliceGetCoordsystemVersion(slice),
                    ensSliceGetSeqregionName(slice),
                    srstart,
                    srend,
                    srstrand);


    ensSliceFetchSequenceSubStr(slice, start, end, strand, &sequence);

    if (*Psequence)
    {
        ajSeqClear(*Psequence);

        ajSeqAssignNameS(*Psequence, name);
        ajSeqAssignSeqS(*Psequence, sequence);
    }
    else
        *Psequence = ajSeqNewNameS(sequence, name);

    ajSeqSetNuc(*Psequence);

    ajStrDel(&sequence);
    ajStrDel(&name);

    return ajTrue;
}
