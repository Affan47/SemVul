gwy_gradient_editor_color_changed(GwyGradientEditor *editor)
{
    g_return_if_fail((gint)editor->pendop.optype == GWY_MARKER_OPERATION_NONE
                     || editor->pendop.optype == GWY_MARKER_OPERATION_MOVE);
    editor->pendop.optype = GWY_MARKER_OPERATION_MOVE;
    editor->pendop.i = gwy_marker_box_get_selected_marker
                                             (GWY_MARKER_BOX(editor->markers));
    gwy_resource_editor_queue_commit(GWY_RESOURCE_EDITOR(editor));
}
