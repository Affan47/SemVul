HPDF_MemStream_FreeData  (HPDF_Stream  stream)
{
    HPDF_MemStreamAttr attr;
    HPDF_UINT i;

    HPDF_PTRACE((" HPDF_MemStream_FreeData\n"));

    if (!stream || stream->type != HPDF_STREAM_MEMORY)
        return;

    attr = (HPDF_MemStreamAttr)stream->attr;

    for (i = 0; i < attr->buf->count; i++)
        HPDF_FreeMem (stream->mmgr, HPDF_List_ItemAt (attr->buf, i));

    HPDF_List_Clear(attr->buf);

    stream->size = 0;
    attr->w_pos = attr->buf_siz;
    attr->w_ptr = NULL;
    attr->r_ptr_idx = 0;
    attr->r_pos = 0;
}
