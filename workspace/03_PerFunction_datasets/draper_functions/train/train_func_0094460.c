gftp_setup_startup_directory (gftp_request * request, const char *option_name)
{
  char *startup_directory, *tempstr;

  gftp_lookup_request_option (request, option_name, &startup_directory);

  if (*startup_directory != '\0' &&
      (tempstr = gftp_expand_path (request, startup_directory)) != NULL)
    {
      gftp_set_directory (request, tempstr);
      g_free (tempstr);
    }
}
