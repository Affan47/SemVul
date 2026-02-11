lang_new_vers_pattern (struct bfd_elf_version_expr *orig,
		       const char *new_name,
		       const char *lang,
		       bfd_boolean literal_p)
{
  struct bfd_elf_version_expr *ret;

  ret = (struct bfd_elf_version_expr *) xmalloc (sizeof *ret);
  ret->next = orig;
  ret->symver = 0;
  ret->script = 0;
  ret->literal = TRUE;
  ret->pattern = literal_p ? new_name : realsymbol (new_name);
  if (ret->pattern == NULL)
    {
      ret->pattern = new_name;
      ret->literal = FALSE;
    }

  if (lang == NULL || strcasecmp (lang, "C") == 0)
    ret->mask = BFD_ELF_VERSION_C_TYPE;
  else if (strcasecmp (lang, "C++") == 0)
    ret->mask = BFD_ELF_VERSION_CXX_TYPE;
  else if (strcasecmp (lang, "Java") == 0)
    ret->mask = BFD_ELF_VERSION_JAVA_TYPE;
  else
    {
      einfo (_("%X%P: unknown language `%s' in version information\n"),
	     lang);
      ret->mask = BFD_ELF_VERSION_C_TYPE;
    }

  return ldemul_new_vers_pattern (ret);
}
