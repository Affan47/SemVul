do_picker_activate(GtkTreeView *src G_GNUC_UNUSED,
                        GtkTreePath *path G_GNUC_UNUSED,
                        GtkTreeViewColumn *col G_GNUC_UNUSED,
                        EntangleCameraPicker *picker)
{
    g_return_if_fail(ENTANGLE_IS_CAMERA_PICKER(picker));

    EntangleCamera *cam;
    cam = entangle_picker_get_selected_camera(picker);
    ENTANGLE_DEBUG("picker activate %p %p", picker, cam);

    if (cam) {
        GValue val;
        memset(&val, 0, sizeof val);
        g_value_init(&val, G_TYPE_OBJECT);
        g_value_set_object(&val, cam);

        g_signal_emit_by_name(picker, "picker-connect", cam);
        g_value_unset(&val);
        g_object_unref(cam);
    }
}
