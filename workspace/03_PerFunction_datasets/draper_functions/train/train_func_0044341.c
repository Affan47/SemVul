file_error_control (GFileError type, FileMode mode)
{
  GString *message;

  switch (mode)
    {
    case RB_MODE:
      message = g_string_new (_("<big><b>Error while opening the file</b></big>\n\n"));
      switch (type)
        {
        case G_FILE_ERROR_PERM:
        case G_FILE_ERROR_ACCES:
          g_string_append (message,
                           _("File cannot be read because you don't have\n" "sufficient rights."));
          break;
        case G_FILE_ERROR_NOENT:
        case G_FILE_ERROR_NXIO:
        case G_FILE_ERROR_NODEV:
          g_string_append (message, _("File cannot be open because it wasn't found."));
          break;
        case G_FILE_ERROR_NAMETOOLONG:
          g_string_append (message,
                           _("File cannot be read because the name is too\n"
                             "long. Usually max length is 255."));
          break;
        case G_FILE_ERROR_TXTBSY:
          g_string_append (message,
                           _("File cannot be open because is used by other\n"
                             "operations or processes."));
          break;
        case G_FILE_ERROR_LOOP:
          g_string_append (message,
                           _("The file you're trying to open is a symbolic\n"
                             "link to another symbolic link.\n"
                             "This then creates an endless cycle of\n"
                             "links and makes it impossible to determine\n"
                             "the final file to be opened."));
          break;
        case G_FILE_ERROR_NOMEM:
          g_string_free (message, TRUE);
          message =
            g_string_new (_("<b><big>Space in memory exhausted!</big></b>\n\n"
                            "Space in virtual memory is exhausted, this makes\n"
                            "it impossible to load the file into RAM."));
          break;
        case G_FILE_ERROR_IO:
          g_string_append (message,
                           _
                           ("File cannot be read because a I/O error has occurred.\n"
                            "Check that the device you are trying to read from\n" "isn't damaged."));
          break;
        case G_FILE_ERROR_FAILED:
        default:
          g_string_append (message, _("An unknown error has occurred while opening the file."));
          break;
        }
      break;
    case WB_MODE:
      message = g_string_new (_("<big><b>Error while saving the file</b></big>\n\n"));
      switch (type)
        {
        case G_FILE_ERROR_ACCES:
          g_string_append (message,
                           _("File cannot be saved because you don't have\n" "sufficient rights."));
          break;
        case G_FILE_ERROR_NAMETOOLONG:
          g_string_append (message,
                           _("File cannot be saved because the name is too\n"
                             "long. Usually max length is 255."));
          break;
        case G_FILE_ERROR_NOMEM:
          g_string_free (message, TRUE);
          message =
            g_string_new (_("<b><big>Space in memory exhausted!</big></b>\n\n"
                            "Space in virtual memory is exhausted, this makes\n"
                            "it impossible to load the file into RAM."));
          break;
        case G_FILE_ERROR_IO:
          g_string_append (message,
                           _
                           ("File cannot be saved because a I/O error has occurred.\n"
                            "Checks that the device you are trying to save from\n" "isn't damaged."));
          break;
        case G_FILE_ERROR_FAILED:
        default:
          g_string_append (message, _("An unknown error has occurred while saving the file."));
          break;
        }
      break;
    default:
      message =
        g_string_new (_("<big><b>Unknown Error</b></big>\n\n"
                        "It wasn't possible to identify the error\n"
                        "occurred while opening the file.\n\n"
                        "Report this bug to: <i>hds619@gmail.com</i>"));
      break;
    }

  _error (message->str);
  g_string_free (message, TRUE);

  return NULL;
}
