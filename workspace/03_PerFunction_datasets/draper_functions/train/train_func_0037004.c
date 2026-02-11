FindAny(const char *str, PDBChain **c, PDBResidue **r, PDBAtom **a, PDBStructureType maxlevel) const
{

  if (!str) return PDB_MODEL;
  if (strlen(str) < 1) return PDB_MODEL;


  char chain_name[4];
  chain_name[0] = str[0];
  if (chain_name[0] == '_') chain_name[0] = ' ';
  chain_name[1] = '\0';


  PDBChain *result = NULL;
  for (int i = 0; i < NChains(); i++) {
    PDBChain *chain = Chain(i);
    if (!strcmp(chain->Name(), chain_name)) {
      result = chain;
      break;
    }
  }


  PDBStructureType level = PDB_MODEL;
  if (result) {
    level = PDB_CHAIN;
    if (c) *c = result;
    const char *strp = (str[1] == '-') ? &str[2] : NULL;
    if (strp && *strp && (maxlevel > level)) {
      level = result->FindAny(strp, r, a, maxlevel);
    }
  }


  return level;
}
