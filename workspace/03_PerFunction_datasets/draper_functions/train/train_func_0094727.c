ensSliceFetchName(const EnsPSlice slice, AjPStr *Pname)
{
    EnsPCoordsystem cs = NULL;

    if (!slice)
        return ajFalse;

    if (!Pname)
        return ajFalse;

    cs = ensSeqregionGetCoordsystem(slice->Seqregion);

    if (*Pname)
        *Pname = ajFmtPrintS(
            Pname,
            "%S:%S:%S:%d:%d:%d",
            ensCoordsystemGetName(cs),
            ensCoordsystemGetVersion(cs),
            ensSeqregionGetName(slice->Seqregion),
            slice->Start,
            slice->End,
            slice->Strand);
    else
        *Pname = ajFmtStr(
            "%S:%S:%S:%d:%d:%d",
            ensCoordsystemGetName(cs),
            ensCoordsystemGetVersion(cs),
            ensSeqregionGetName(slice->Seqregion),
            slice->Start,
            slice->End,
            slice->Strand);

    return ajTrue;
}
