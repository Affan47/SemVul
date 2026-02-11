grid_get_DN(gchar *certificate_fullpath)
{
gint i, j, status;
gchar *cmd, *out, *err, *subject=NULL;
GError *error=NULL;

cmd = g_strdup_printf("openssl x509 -noout -in %s -subject", certificate_fullpath);


if (g_spawn_command_line_sync(cmd, &out, &err, &status, &error))
  {
  for (i=0 ; i<8000 ; i++)
    {
    if (out[i] == '/')
      {


      for (j=i ; j<9000 ; j++)
        {
        if (out[j] == '\0')
          break;
        }
      subject = g_strndup(&out[i], j-i-1);
      break;
      }
    }
  }
g_free(cmd);

return(subject);
}
