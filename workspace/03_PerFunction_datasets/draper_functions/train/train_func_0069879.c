find_label(char *name)
{
  List_iterator_fast<sp_label_t> li(m_label);
  sp_label_t *lab;

  while ((lab= li++))
    if (my_strcasecmp(system_charset_info, name, lab->name) == 0)
      return lab;


  if (m_parent && (m_label_scope == LABEL_DEFAULT_SCOPE))
    return m_parent->find_label(name);
  return NULL;
}
