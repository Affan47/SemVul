FindAny(const char *str, PDBModel **m, PDBChain **c, PDBResidue **r, PDBAtom **a, PDBStructureType maxlevel) const
{

  if (!str) return PDB_FILE;
  if (strlen(str) < 1) return PDB_FILE;
  char *strp = (char *) str;
  while (*strp) { if (*strp == '-') break; strp++; }


  if (((strp - str) == 4) && (*strp == '-'))
    return FindAny(&str[5], m, c, r, a, maxlevel);


  char save = *strp;
  *strp = '\0';


  PDBModel *result = NULL;
  for (int i = 0; i < NModels(); i++) {
    PDBModel *model = Model(i);
    if (!strcmp(model->Name(), str)) {
      result = model;
      break;
    }
  }


  *strp = save;


  PDBStructureType level = PDB_FILE;
  if (result) {
    level = PDB_MODEL;
    if (m) *m = result;
    if (strp && *strp && (maxlevel > level)) {
      level = result->FindAny(strp+1, c, r, a, maxlevel);
    }
  }


  return level;
}
