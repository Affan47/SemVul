dir_load_doc(Dir* d, GError** err)
{
  gboolean xml_already_exists = TRUE;
  gboolean need_backup = FALSE;
  struct stat statbuf;

  g_return_if_fail(d->doc == NULL);

  if (stat(d->xml_filename, &statbuf) < 0)
    {
      switch (errno)
        {
        case ENOENT:
          xml_already_exists = FALSE;
          break;
        case ENOTDIR:
#ifdef ELOOP
        case ELOOP:
#endif
        case EFAULT:
        case EACCES:
        case ENOMEM:
        case ENAMETOOLONG:
        default:

          gconf_set_error(err, GCONF_ERROR_FAILED, _("Failed to stat `%s': %s"),
                          d->xml_filename, g_strerror(errno));
          return;
          break;
        }
    }

  if (statbuf.st_size == 0)
    {
      xml_already_exists = FALSE;
    }

  if (xml_already_exists)
    {
      GError *tmp_err;
      gboolean error_was_fatal;

      error_was_fatal = FALSE;
      tmp_err = NULL;
      d->doc = my_xml_parse_file (d->xml_filename, &tmp_err);

      if (tmp_err != NULL)
        {
          gconf_log (GCL_WARNING,
                     "%s", tmp_err->message);


          if (tmp_err->domain == G_FILE_ERROR)
            error_was_fatal = TRUE;

          g_error_free (tmp_err);
        }

      if (error_was_fatal)
        return;
    }


  if (d->doc == NULL)
    {
      if (xml_already_exists)
        need_backup = TRUE;


      d->doc = xmlNewDoc((xmlChar *)"1.0");
    }

  if (d->doc->xmlRootNode == NULL)
    {

      d->doc->xmlRootNode = xmlNewDocNode(d->doc, NULL, "gconf", NULL);
    }
  else if (strcmp((char*)d->doc->xmlRootNode->name, "gconf") != 0)
    {
      xmlFreeDoc(d->doc);
      d->doc = xmlNewDoc((xmlChar*)"1.0");
      d->doc->xmlRootNode = xmlNewDocNode(d->doc, NULL, (xmlChar *)"gconf", NULL);
      need_backup = TRUE;
    }
  else
    {


      dir_fill_cache_from_doc(d);
    }

  if (need_backup)
    {


      gchar* backup = g_strconcat(d->xml_filename, ".bak", NULL);
      int fd;

      g_rename(d->xml_filename, backup);


      fd = g_open(d->xml_filename, O_CREAT | O_WRONLY | O_TRUNC, d->file_mode);
      if (fd >= 0)
        close(fd);

      g_free(backup);
    }

  g_assert(d->doc != NULL);
  g_assert(d->doc->xmlRootNode != NULL);
}
