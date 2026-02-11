vtkParseHierarchy_GetProperty(
  const HierarchyEntry *entry, const char *property)
{
  int i;
  size_t k;

  if (entry)
    {
    for (i = 0; i < entry->NumberOfProperties; i++)
      {

      k = vtkParse_NameLength(entry->Properties[i]);
      if (k == strlen(property) &&
          strncmp(entry->Properties[i], property, k) == 0)
        {
        if (entry->Properties[i][k] == ' ' ||
            entry->Properties[i][k] == '=') { k++; }
        return &entry->Properties[i][k];
        }
      }
    }

  return NULL;
}
