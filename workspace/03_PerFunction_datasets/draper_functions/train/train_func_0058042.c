secfile_entry_by_path(const struct section_file *secfile,
                                    const char *entry_path)
{
  char fullpath[MAX_LEN_SECPATH];
  char *ent_name;
  size_t len;
  struct section *psection;

  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != secfile, NULL);

  sz_strlcpy(fullpath, entry_path);


  len = strlen(fullpath);
  if (len > 2 && fullpath[len - 2] == ',' && fullpath[len - 1] == '0') {
    fullpath[len - 2] = '\0';
  }

  if (NULL != secfile->hash.entries) {
    struct entry *pentry;

    if (entry_hash_lookup(secfile->hash.entries, fullpath, &pentry)) {
      entry_use(pentry);
    }
    return pentry;
  }


  ent_name = strchr(fullpath, '.');
  if (!ent_name) {
    return NULL;
  }


  *ent_name++ = '\0';
  psection = secfile_section_by_name(secfile, fullpath);
  if (psection) {
    return section_entry_by_name(psection, ent_name);
  } else {
    return NULL;
  }
}
