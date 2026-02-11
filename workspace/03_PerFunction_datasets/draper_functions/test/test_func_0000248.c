ppdMarkOption(ppd_file_t *ppd,
              const char *option,
              const char *choice)
{
  DEBUG_printf(("ppdMarkOption(ppd=%p, option=\"%s\", choice=\"%s\")",
        	ppd, option, choice));


  if (!ppd || !option || !choice)
    return (0);


  ppd_mark_option(ppd, option, choice);


  return (ppdConflicts(ppd));
}
