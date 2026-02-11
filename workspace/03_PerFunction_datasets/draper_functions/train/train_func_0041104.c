technology_load(struct section_file *file,
                                    const char* path, int plrno)
{
  char path_with_name[128];
  const char* name;
  struct advance *padvance;
  int id;

  fc_snprintf(path_with_name, sizeof(path_with_name),
              "%s_name", path);

  name = secfile_lookup_str(file, path_with_name, plrno);
  if (!name) {
    id = secfile_lookup_int_default(file, -1, path, plrno);
    name = old_tech_name(id);
    if (!name) {
      log_fatal("%s: value (%d) out of range.", path, id);
      exit(EXIT_FAILURE);
    }
  }

  if (fc_strcasecmp(name, "A_FUTURE") == 0) {
    return A_FUTURE;
  }
  if (fc_strcasecmp(name, "A_NONE") == 0) {
    return A_NONE;
  }
  if (fc_strcasecmp(name, "A_UNSET") == 0) {
    return A_UNSET;
  }
  if (name[0] == '\0') {

    return A_UNKNOWN;
  }

  padvance = advance_by_rule_name(name);
  if (NULL == padvance) {
    log_fatal("%s: unknown technology \"%s\".", path_with_name, name);
    exit(EXIT_FAILURE);
  }
  return advance_number(padvance);
}
