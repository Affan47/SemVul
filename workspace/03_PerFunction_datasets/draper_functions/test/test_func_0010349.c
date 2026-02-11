section_destroy(struct section *psection)
{
  struct section_file *secfile;

  SECFILE_RETURN_IF_FAIL(NULL, psection, NULL != psection);

  section_clear_all(psection);

  if ((secfile = psection->secfile)) {

    if (section_list_remove(secfile->sections, psection)) {

      return;
    }
    if (NULL != secfile->hash.sections) {
      section_hash_remove(secfile->hash.sections, psection->name);
    }
  }

  entry_list_destroy(psection->entries);
  free(psection->name);
  free(psection);
}
