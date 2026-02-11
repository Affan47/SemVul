gnc_item_edit_focus_out (GncItemEdit *item_edit)
{
    GdkEventFocus ev;

    g_return_if_fail (item_edit != NULL);
    g_return_if_fail (GNC_IS_ITEM_EDIT(item_edit));

    ev.type = GDK_FOCUS_CHANGE;
    ev.window = GTK_WIDGET (item_edit->sheet)->window;
    ev.in = FALSE;
    gtk_widget_event (item_edit->editor, (GdkEvent*) &ev);
    queue_sync(item_edit);
}
