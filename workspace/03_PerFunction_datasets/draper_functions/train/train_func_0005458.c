mapimg_client_save(const char *filename)
{
  if (!mapimg_client_createmap(filename)) {
    char msg[512];

    fc_snprintf(msg, sizeof(msg), "(%s)", mapimg_error());
    popup_notify_dialog("Error", "Error Creating the Map Image!", msg);
  }
}
