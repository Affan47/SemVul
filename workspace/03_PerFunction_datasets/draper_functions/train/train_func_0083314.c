paste_clipboard_wait_for_buffer (gpaint_canvas *canvas)
{
    gpaint_clipboard *clipboard = canvas_clipboard(canvas);
    GdkAtom *targets;
    gint n_targets;
    GdkAtom result = GDK_NONE;

    targets = paste_clipboard_wait_for_targets (&n_targets);

    if (targets)
    {
	GSList *list;

        for (list = clipboard->pixbuf_formats; list; list = g_slist_next (list))
        {
          GdkPixbufFormat  *format = list->data;
          gchar           **mime_types;
          gchar           **type;

          g_print ("checking pixbuf format '%s'\n",
                   gdk_pixbuf_format_get_name (format));

          mime_types = gdk_pixbuf_format_get_mime_types (format);

          for (type = mime_types; *type; type++)
          {
              gchar   *mime_type = *type;
              GdkAtom  atom      = gdk_atom_intern (mime_type, FALSE);
              gint     i;

              g_print (" - checking mime type '%s'\n", mime_type);

              for (i = 0; i < n_targets; i++)
              {
                  if (targets[i] == atom)
                  {
                      result = atom;
                      break;
                  }
              }

              if (result != GDK_NONE)
                break;
          }

          g_strfreev (mime_types);

          if (result != GDK_NONE)
              break;
        }

        g_free (targets);
    }

    return result;
}
