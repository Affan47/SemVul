help_sort_by_score(help_node_t *n1,
                   help_node_t *n2)
{
  int		diff;


  DEBUG_printf(("2help_sort_by_score(n1=%p(%d \"%s\" \"%s\"), "
                "n2=%p(%d \"%s\" \"%s\")",
                n1, n1->score, n1->section, n1->text,
                n2, n2->score, n2->section, n2->text));

  if (n1->score != n2->score)
    return (n2->score - n1->score);

  if (n1->section && !n2->section)
    return (1);
  else if (!n1->section && n2->section)
    return (-1);
  else if (n1->section && n2->section &&
           (diff = strcmp(n1->section, n2->section)) != 0)
    return (diff);

  return (_cups_strcasecmp(n1->text, n2->text));
}
