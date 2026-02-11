gwy_tool_mask_editor_selection_changed(GwyPlainTool *plain_tool,
                                       G_GNUC_UNUSED gint hint)
{
    GwyDataField *mfield;
    GwyToolMaskEditor *tool;
    GQuark quark;
    gint xres, yres;
    gdouble sel[2];
    gdouble fillvalue, r;
    gint isel[2];

    tool = GWY_TOOL_MASK_EDITOR(plain_tool);
    if (tool->in_setup || tool->args.style != MASK_EDIT_STYLE_DRAWING)
        return;

    if (tool->args.tool == MASK_TOOL_PAINT_DRAW)
        fillvalue = 1.0;
    else if (tool->args.tool == MASK_TOOL_PAINT_ERASE)
        fillvalue = 0.0;
    else
        return;


    if (!plain_tool->data_field || !plain_tool->selection
        || !gwy_selection_get_object(plain_tool->selection, 0, sel)) {
        tool->drawing_started = FALSE;
        return;
    }

    isel[0] = floor(gwy_data_field_rtoj(plain_tool->data_field, sel[0]));
    isel[1] = floor(gwy_data_field_rtoi(plain_tool->data_field, sel[1]));

    quark = gwy_app_get_mask_key_for_id(plain_tool->id);

    mfield = gwy_tool_mask_editor_maybe_add_mask(plain_tool, quark);
    xres = gwy_data_field_get_xres(mfield);
    yres = gwy_data_field_get_yres(mfield);
    r = tool->args.radius - 0.5;
    if (isel[0] >= 0 && isel[0] < xres && isel[1] >= 0 && isel[1] < yres) {
        if (!tool->drawing_started) {
            gwy_app_undo_qcheckpointv(plain_tool->container, 1, &quark);
            gwy_data_field_circular_area_fill(mfield, isel[0], isel[1],
                                              r, fillvalue);
        }
        else {
            gint xy[4];

            xy[0] = tool->oldisel[0];
            xy[1] = tool->oldisel[1];
            xy[2] = isel[0];
            xy[3] = isel[1];
            if (xy[2] < xy[0]) {
                GWY_SWAP(gdouble, xy[0], xy[2]);
                GWY_SWAP(gdouble, xy[1], xy[3]);
            }
            xy[2] -= xy[0] - 1;
            xy[3] -= xy[1] - 1;
            gwy_data_field_paint_wide_line(mfield, xy[0], xy[1], xy[2], xy[3],
                                           r, fillvalue);
        }
        gwy_data_field_data_changed(mfield);
        tool->oldisel[0] = isel[0];
        tool->oldisel[1] = isel[1];
        tool->drawing_started = TRUE;
    }
}
