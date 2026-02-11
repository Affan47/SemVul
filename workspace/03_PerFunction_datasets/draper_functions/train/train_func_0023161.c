stasche_write_set_emt(csbe_context *cx, const Hmdf_table *hmdf, int emt_no)
{
    if (opt_stasche_end_flush)
        ompcbe_write_flush(cx);

    ompcbe_write_frame_pointer(cx);
    csbe_printf(cx, "STASCHE_EMT%d = %d;\n", hmdf->mtg_id, emt_no);

    if (opt_stasche_end_flush)
        ompcbe_write_flush(cx);
}
