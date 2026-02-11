gdm_display_get_x11_authority_file (GdmDisplay *display,
                                    char      **filename,
                                    GError    **error)
{
        g_return_val_if_fail (GDM_IS_DISPLAY (display), FALSE);
        g_return_val_if_fail (filename != NULL, FALSE);

        if (display->priv->access_file != NULL) {
                *filename = gdm_display_access_file_get_path (display->priv->access_file);
        } else {
                *filename = NULL;
        }

        return TRUE;
}
