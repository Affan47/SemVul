inset_length_changed(GtkEntry *entry,
                     PixmapSaveControls *controls)
{
    PixmapSaveArgs *args = controls->args;
    GwyDataField *dfield;
    const gchar *text;

    dfield = args->dfield;
    text = gtk_entry_get_text(entry);
    g_free(args->inset_length);
    if (inset_length_ok(dfield, text)) {

        args->inset_length = g_strdup(text);
    }
    else {
        args->inset_length = scalebar_auto_length(dfield, NULL);
        gtk_entry_set_text(entry, args->inset_length);
    }

    if (controls->in_update || args->xytype != PIXMAP_SCALEBAR)
        return;

    save_update_preview(controls);
}
