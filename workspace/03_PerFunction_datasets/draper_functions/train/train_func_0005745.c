gx_path_pop_close_notes(gx_path * ppath, segment_notes notes)
{
    subpath *psub = ppath->current_subpath;
    segment *pseg;
    segment *prev;

    if (psub == 0 || (pseg = psub->last) == 0 ||
        pseg->type != s_line
        )
        return_error(gs_error_unknownerror);
    prev = pseg->prev;
    prev->next = 0;
    psub->last = prev;
    gs_free_object(ppath->memory, pseg, "gx_path_pop_close_subpath");
    return gx_path_close_subpath_notes(ppath, notes);
}
