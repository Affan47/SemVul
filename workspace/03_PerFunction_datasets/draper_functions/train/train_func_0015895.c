HPDF_EmbeddedFile_New  (HPDF_MMgr  mmgr,
                        HPDF_Xref  xref,
                        const char *file)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Dict ef;
    HPDF_String name;
    HPDF_Dict eff;
    HPDF_Dict filestream;
    HPDF_Stream stream;

    ef = HPDF_Dict_New (mmgr);
    if (!ef)
        return NULL;
    if (HPDF_Xref_Add (xref, ef) != HPDF_OK)
        return NULL;

    filestream = HPDF_DictStream_New (mmgr, xref);
    if (!filestream)
        return NULL;
    stream = HPDF_FileReader_New (mmgr, file);
    if (!stream)
        return NULL;
    HPDF_Stream_Free(filestream->stream);
    filestream->stream = stream;
    filestream->filter = HPDF_STREAM_FILTER_FLATE_DECODE;

    eff = HPDF_Dict_New (mmgr);
    if (!eff)
        return NULL;

    name = HPDF_String_New (mmgr, file, NULL);
    if (!name)
        return NULL;

    ret += HPDF_Dict_AddName (ef, "Type", "F");
    ret += HPDF_Dict_Add (ef, "F", name);
    ret += HPDF_Dict_Add (ef, "EF", eff);
    ret += HPDF_Dict_Add (eff, "F", filestream);

    if (ret != HPDF_OK)
        return NULL;

    return ef;
}
