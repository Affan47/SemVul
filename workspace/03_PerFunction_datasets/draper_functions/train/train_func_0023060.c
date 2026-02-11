editor_cancel_button_clicked_cb (GtkButton *b, GncSxEditorDialog2 *sxed)
{

    if (!sxed_confirmed_cancel (sxed))
        return;

    gnc_close_gui_component_by_data (DIALOG_SCHEDXACTION2_EDITOR_CM_CLASS,
                                     sxed);
}
