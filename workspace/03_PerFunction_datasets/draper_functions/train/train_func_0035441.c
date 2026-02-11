gp_archive_remove_index(gp_archive_type *archive)
{
  gp_archive_type *member = NULL;


  if (gp_archive_have_index(archive)) {
    member = archive;
    archive = archive->next;
    gp_archive_free_member(member);
  }

  return archive;
}
