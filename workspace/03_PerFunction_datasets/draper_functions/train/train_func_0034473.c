addRepoIds(const _omni_ValueIds* repoIds, CORBA::Long current)
{
  OutputTableEntry* e;

  CORBA::ULong hashval = repoIds->hashval % pd_table_size;

  for (e = pd_table[hashval]; e; e = e->next) {
    if (e->kind == OT_REPOIDS && listsMatch(e->repoIds, repoIds))
      return e->position;
  }
  e = new OutputTableEntry(repoIds, current, pd_table[hashval]);
  pd_table[hashval] = e;
  return -1;
}
