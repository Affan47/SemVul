gs_font_alloc(gs_memory_t *mem, gs_memory_type_ptr_t pstype,
              const gs_font_procs *procs, gs_font_dir *dir,
              client_name_t cname)
{
    gs_font *pfont = gs_alloc_struct(mem, gs_font, pstype, cname);

    if (pfont == 0)
        return 0;
#if 1

    memset(pfont, 0, pstype->ssize);
    pfont->memory = mem;
    pfont->dir = dir;
    gs_font_notify_init(pfont);
    pfont->id = gs_next_ids(mem, 1);
    pfont->base = pfont;
    pfont->ExactSize = pfont->InBetweenSize = pfont->TransformedChar =
        fbit_use_outlines;
    pfont->procs = *procs;
#else


    pfont->next = pfont->prev = 0;
    pfont->memory = mem;
    pfont->dir = dir;
    pfont->is_resource = false;
    gs_font_notify_init(pfont);
    pfont->id = gs_next_ids(mem, 1);
    pfont->base = pfont;
    pfont->client_data = 0;

    pfont->BitmapWidths = false;
    pfont->ExactSize = pfont->InBetweenSize = pfont->TransformedChar =
        fbit_use_outlines;
    pfont->WMode = 0;
    pfont->PaintType = 0;
    pfont->StrokeWidth = 0;
    pfont->is_cached = false;
    pfont->procs = *procs;
    memset(&pfont->orig_FontMatrix, 0, sizeof(pfont->orig_FontMatrix));
#endif

    return pfont;
}
