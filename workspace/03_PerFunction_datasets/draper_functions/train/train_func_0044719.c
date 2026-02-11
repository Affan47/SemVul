run_noninteractive(WshedArgs *args,
                   GwyContainer *data,
                   GwyDataField *dfield,
                   GQuark mquark,
                   gint id)
{
    GwyDataField *mfield;

    mfield = create_mask_field(dfield);
    if (mask_process(dfield, mfield, args,
                     gwy_app_find_window_for_channel(data, id))) {
        gwy_app_undo_qcheckpointv(data, 1, &mquark);
        gwy_container_set_object(data, mquark, mfield);
    }
    g_object_unref(mfield);
}
