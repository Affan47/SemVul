remove_directory(void)
{
  if (getpid() != temp_dir_setup_in_pid) {

    return;
  }

  rm_rf(temp_dir);
}
