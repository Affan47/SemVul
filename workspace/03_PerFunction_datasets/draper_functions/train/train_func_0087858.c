load_cogl_texture (const char *type,
                   const char *file)
{
  GError *error = NULL;

  CoglHandle retval = cogl_texture_new_from_file (file,
                                                  COGL_TEXTURE_NO_SLICING,
                                                  COGL_PIXEL_FORMAT_ANY,
                                                  &error);
  if (error != NULL)
    {
      g_print ("Unable to load %s image: %s\n", type, error->message);
      g_error_free (error);
      exit (EXIT_FAILURE);
    }

  return retval;
}
