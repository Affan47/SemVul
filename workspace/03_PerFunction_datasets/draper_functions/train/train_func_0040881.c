cos_stream_release_pieces(cos_stream_t *pcs)
{
    gx_device_pdf *pdev = pcs->pdev;
    stream *s = pdev->streams.strm;
    gs_offset_t position = stell(s), position0 = position;
    gs_memory_t *mem = cos_object_memory((cos_object_t *)pcs);

    while (pcs->pieces != NULL &&
                position == pcs->pieces->position + pcs->pieces->size) {
        cos_stream_piece_t *p = pcs->pieces;

        position -= p->size;
        pcs->pieces = p->next;
        gs_free_object(mem, p, "cos_stream_release_pieces");
    }
    if (position0 != position)
        if (sseek(s, position) < 0)
            return_error(gs_error_ioerror);
    return 0;
}
