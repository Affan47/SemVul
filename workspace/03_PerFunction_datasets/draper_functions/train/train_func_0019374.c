rgbe_header_write (const rgbe_header *header,
                   FILE              *f)
{
  gchar    *line    = NULL;
  gboolean  success = FALSE;
  gint      len;

  g_return_val_if_fail (header, FALSE);
  g_return_val_if_fail (f,      FALSE);


  line = g_strconcat (RADIANCE_MAGIC, "\n", NULL);
  if (!rgbe_write_line (f, line))
      goto cleanup;


  len = strlen (header->software);
  if (len  == 0 || len > RGBE_MAX_SOFTWARE_LEN - 1)
    {
      line = g_strconcat ("SOFTWARE=", PACKAGE_STRING, "\n", NULL);
    }
  else
    {
      line = g_strconcat ("SOFTWARE=", header->software, "\n", NULL);
    }
  if (!rgbe_write_line (f, line))
      goto cleanup;


  g_return_val_if_fail (header->format < FORMAT_UNKNOWN,                     FALSE);
  g_return_val_if_fail (header->format < G_N_ELEMENTS (RGBE_FORMAT_STRINGS), FALSE);
  line = g_strconcat ("FORMAT=",
                      RGBE_FORMAT_STRINGS[header->format],
                      "\n", NULL);
  if (!rgbe_write_line (f, line))
      goto cleanup;


  if (header->exposure != 1.0)
    {
      gchar exp_line[G_ASCII_DTOSTR_BUF_SIZE + 1];
      line = g_strconcat ("EXPOSURE=",
                          g_ascii_dtostr (exp_line,
                                          G_N_ELEMENTS (exp_line),
                                          header->exposure),
                          "\n",
                          NULL);
      if (!rgbe_write_line (f, line))
          goto cleanup;
    }


  if (header->colorcorr [OFFSET_R] != 1.0 &&
      header->colorcorr [OFFSET_G] != 1.0 &&
      header->colorcorr [OFFSET_B] != 1.0)
  {
    gchar corr_line[G_ASCII_DTOSTR_BUF_SIZE + 1][RGBE_NUM_RGB];
    line = g_strconcat ("COLORCORR=",
                        g_ascii_dtostr (corr_line[OFFSET_R],
                                        G_N_ELEMENTS (corr_line[OFFSET_R]),
                                        header->colorcorr[OFFSET_R]), " ",
                        g_ascii_dtostr (corr_line[OFFSET_G],
                                        G_N_ELEMENTS (corr_line[OFFSET_G]),
                                        header->colorcorr[OFFSET_G]), " ",
                        g_ascii_dtostr (corr_line[OFFSET_B],
                                        G_N_ELEMENTS (corr_line[OFFSET_B]),
                                        header->colorcorr[OFFSET_R]),
                        "\n",
                        NULL);
    if (!rgbe_write_line (f, line))
        goto cleanup;
  }


  {
    const guint res_line_sz = strlen ("\n")
                            + strlen ("-Y ") * 2
                            + strlen (G_STRINGIFY (RGBE_MAX_SCANLINE_WIDTH)) * 2
                            + strlen ("\n")
                            + 1;
    gint err;

    line = g_malloc (res_line_sz * sizeof (line[0]));
    err  = snprintf (line, res_line_sz,
                     "\n-Y %hu +X %hu\n",
                     header->y_axis.size,
                     header->x_axis.size);
    if (err < 0 || !rgbe_write_line (f, line))
        goto cleanup;
  }

  success = TRUE;
cleanup:
  return success;
}
