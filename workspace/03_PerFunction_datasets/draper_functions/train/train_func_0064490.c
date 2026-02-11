load_pixmap(const char *keymap_dir, char *filename_buffer)
{
  char *ptr = strchr(filename_buffer, '\n');
  if (ptr != NULL)
    *ptr = '\0';

  string dir(keymap_dir);
  string filename = dir + filename_buffer;
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename.c_str(), NULL);

  if (pixbuf == NULL)
    {
      DBG(0, form("KCemu/warning",
                  "KeyboardWindow::load_pixmap((): can't load keyboard pixmap '%s'\n",
                  filename.c_str()));
    }

  return pixbuf;
}
