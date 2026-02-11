gp_archive_free_member(gp_archive_type *archive)
{

  if (archive->file != NULL)
    free(archive->file);
  if (archive != NULL)
    free(archive);

  return 0;
}
