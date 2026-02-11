check_datadir_env (void)
{
  char* data_dir;
  dmsg (D_SYSTEM, "looking for HEROES_DATA_DIR or HEROES_DATADIR...");
  if ((data_dir = getenv ("HEROES_DATA_DIR")) ||
      (data_dir = getenv ("HEROES_DATADIR"))) {
    dmsg (D_SYSTEM,"... found: %s", data_dir);
    set_rsc_file ("data-dir", data_dir, false);
  } else {
    dmsg (D_SYSTEM, "... not found.");
  }
}
