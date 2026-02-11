rsvg_handle_new_from_stream_sync (GInputStream   *input_stream,
                                  GFile          *base_file,
                                  RsvgHandleFlags flags,
                                  GCancellable    *cancellable,
                                  GError         **error)
{
    RsvgHandle *handle;

    g_return_val_if_fail (G_IS_INPUT_STREAM (input_stream), NULL);
    g_return_val_if_fail (base_file == NULL || G_IS_FILE (base_file), NULL);
    g_return_val_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable), NULL);
    g_return_val_if_fail (error == NULL || *error == NULL, NULL);

    handle = rsvg_handle_new_with_flags (flags);

    if (base_file)
        rsvg_handle_set_base_gfile (handle, base_file);

    if (!rsvg_handle_read_stream_sync (handle, input_stream, cancellable, error)) {
        g_object_unref (handle);
        return NULL;
    }

    return handle;
}
