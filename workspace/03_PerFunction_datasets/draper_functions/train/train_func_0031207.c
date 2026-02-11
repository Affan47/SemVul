write_sample_clnt (definition * def)
{
  version_list *vp;
  int count = 0;

  if (def->def_kind != DEF_PROGRAM)
    return 0;

  for (vp = def->def.pr.versions; vp != NULL; vp = vp->next)
    {
      write_sample_client (def->def_name, vp);
      ++count;
    }
  return count;
}
