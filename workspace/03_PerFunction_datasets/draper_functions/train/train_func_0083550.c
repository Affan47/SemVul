init_archive_psi_keys(void)
{
  const char* category= "archive";
  int count;

  if (PSI_server == NULL)
    return;

  count= array_elements(all_archive_mutexes);
  PSI_server->register_mutex(category, all_archive_mutexes, count);

  count= array_elements(all_archive_files);
  PSI_server->register_file(category, all_archive_files, count);
}
