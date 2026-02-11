stop_io(void)
{
  if (triggered_rep == true) {
    if (io_mode() == io_read) {
      fclose(f1_rep);
      f1_rep = 0;
      clean_child(true);
    }
    else
      clean_child(false);

    triggered_rep = false;
  }
}
