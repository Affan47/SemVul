gdk_pixbuf_real_save_to_callback (GdkPixbuf         *pixbuf,
                                  GdkPixbufSaveFunc  save_func,
                                  gpointer           user_data,
                                  const char        *type,
                                  gchar            **keys,
                                  gchar            **values,
                                  GError           **error)
{
        gboolean ret;
        GdkPixbufModule *image_module = NULL;

        image_module = _gdk_pixbuf_get_named_module (type, error);

        if (image_module == NULL)
                return FALSE;

        if (!_gdk_pixbuf_load_module (image_module, error))
                return FALSE;

        if (image_module->save_to_callback) {

                ret = (* image_module->save_to_callback) (save_func, user_data,
                                                          pixbuf, keys, values,
                                                          error);
        } else if (image_module->save) {

                ret = save_to_callback_with_tmp_file (image_module, pixbuf,
                                                      save_func, user_data,
                                                      keys, values,
                                                      error);
        } else {

                g_set_error (error,
                             GDK_PIXBUF_ERROR,
                             GDK_PIXBUF_ERROR_UNSUPPORTED_OPERATION,
                             _("This build of gdk-pixbuf does not support saving the image format: %s"),
                             type);
                ret = FALSE;
        }

        return ret;
}
