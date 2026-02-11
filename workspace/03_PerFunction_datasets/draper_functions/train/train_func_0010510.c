gnucash_sheet_focus_in_event (GtkWidget *widget, GdkEventFocus *event)
{
    GnucashSheet *sheet = GNUCASH_SHEET(widget);

    if (GTK_WIDGET_CLASS(sheet_parent_class)->focus_in_event)
        (*GTK_WIDGET_CLASS (sheet_parent_class)->focus_in_event)
        (widget, event);

    gnc_item_edit_focus_in (GNC_ITEM_EDIT(sheet->item_editor));
    gtk_im_context_focus_in(sheet->im_context);

#ifdef G_OS_WIN32
    gnucash_sheet_im_context_reset(sheet);
#endif

    return FALSE;
}
