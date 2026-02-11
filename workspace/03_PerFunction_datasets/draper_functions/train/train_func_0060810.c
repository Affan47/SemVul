HB_FreeFace(HB_Face face)
{
    if (!face)
        return;
    if (face->gpos)
        HB_Done_GPOS_Table(face->gpos);
    if (face->gsub)
        HB_Done_GSUB_Table(face->gsub);
    if (face->gdef)
        HB_Done_GDEF_Table(face->gdef);
    if (face->buffer)
        hb_buffer_free(face->buffer);
    if (face->tmpAttributes)
        free(face->tmpAttributes);
    if (face->tmpLogClusters)
        free(face->tmpLogClusters);
    free(face);
}
