InfpFindSection(PINFCACHE Cache,
                PCWSTR Name)
{
  PINFCACHESECTION Section = NULL;

  if (Cache == NULL || Name == NULL)
    {
      return NULL;
    }


  Section = Cache->FirstSection;
  while (Section != NULL)
    {
      if (strcmpiW(Section->Name, Name) == 0)
        {
          return Section;
        }


      Section = Section->Next;
    }

  return NULL;
}
