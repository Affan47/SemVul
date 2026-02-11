splot_check_colors (gushort maxcolorid, gint *ncolors_used,
  gushort *colors_used, GGobiData *d, ggobid *gg)
{
  colorschemed *scheme = gg->activeColorScheme;
  gchar *message;

  if (maxcolorid >= scheme->n) {

    if (*ncolors_used > scheme->n) {
      message = g_strdup_printf ("The number of colors in use (%d) is greater than than\nthe number of colors in the current scheme (%d).\nColors are being reassigned.", *ncolors_used, scheme->n);
      quick_message (message, false);
      g_free (message);
    }
    else {
      message = g_strdup_printf ("The largest color id in use (%d) is too large for\nthe number of colors in the current scheme (%d).\nColors are being reassigned.", maxcolorid, scheme->n);
      quick_message (message, false);
      g_free (message);
   }

    colors_remap (scheme, true, gg);

    datad_colors_used_get (ncolors_used, colors_used, d, gg);
  }
}
