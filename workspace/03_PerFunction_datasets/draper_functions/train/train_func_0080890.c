gdk_pixbuf__xpm_image_stop_load (gpointer data,
                                 GError **error)
{
       XPMContext *context = (XPMContext*) data;
       GdkPixbuf *pixbuf;
       gboolean retval = FALSE;

       g_return_val_if_fail (data != NULL, FALSE);

       fflush (context->file);
       rewind (context->file);
       if (context->all_okay) {
               pixbuf = gdk_pixbuf__xpm_image_load (context->file, error);

               if (pixbuf != NULL) {
		       if (context->prepare_func)
			       (* context->prepare_func) (pixbuf,
							  NULL,
							  context->user_data);
		       if (context->update_func)
			       (* context->update_func) (pixbuf, 0, 0, pixbuf->width, pixbuf->height, context->user_data);
                       g_object_unref (pixbuf);

                       retval = TRUE;
               }
       }

       fclose (context->file);
       g_unlink (context->tempname);
       g_free (context->tempname);
       g_free ((XPMContext *) context);

       return retval;
}
