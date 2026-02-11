ufo_file_camera_initable_init (GInitable *initable,
                               GCancellable *cancellable,
                               GError **error)
{
    g_return_val_if_fail (UCA_IS_FILE_CAMERA (initable), FALSE);
    return TRUE;
}
