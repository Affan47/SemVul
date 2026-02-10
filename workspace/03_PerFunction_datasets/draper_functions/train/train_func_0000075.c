gz_path_add_line_notes(gx_path * ppath, fixed x, fixed y, segment_notes notes)
{
    subpath *psub;
    line_segment *lp;

    if (ppath->bbox_set)
        check_in_bbox(ppath, x, y);
    path_open();
    path_alloc_segment(lp, line_segment, &st_line, s_line, notes,
                       "gx_path_add_line");
    path_alloc_link(lp);
    path_set_point(lp, x, y);
    path_update_draw(ppath);
    trace_segment("[P]", ppath->memory, (segment *) lp);
    return 0;
}
