ARCHIVE_dir_next(char **name, int *len, int attr)
{
	ARCH_SYMBOL *asym;
  SYMBOL *sym;
  char *s = NULL;
  int l = 0;
  int lenp;


  if (!arch_dir)
    return TRUE;

	lenp = STRING_length(arch_prefix);

  for(;;)
  {
    if (arch_index >= arch_dir->header.n_symbol)
      return TRUE;


		asym = &arch_dir->symbol[arch_dir->sort[arch_index]];
		sym = &asym->sym;

    if (arch_pattern == NULL)
      break;

    arch_index++;

		if (attr == GB_STAT_DIRECTORY && (asym->pos >= 0))
			continue;

		if (sym->len < lenp)
			continue;

		if (lenp)
		{
			if (strncmp(sym->name, arch_prefix, lenp))
				continue;
		}
		else
		{
			if (!strncmp(sym->name, "/", 1))
				continue;
		}

		s = sym->name + lenp;
		l = sym->len - lenp;

		if (l < 0)
			continue;

		if (memchr(s, '/', l))
			continue;

    if (!REGEXP_match(arch_pattern, STRING_length(arch_pattern), s, l))
    	continue;

		break;
	}

  *name = s;
  *len = l;
  return FALSE;
}
