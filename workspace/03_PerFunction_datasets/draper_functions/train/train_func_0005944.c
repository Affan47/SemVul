a2obj(char *s, globus_rls_obj_type_t *ot)

{
  if (strcasecmp(s, "lfn") == 0)
    *ot = globus_rls_obj_lrc_lfn;
  else if (strcasecmp(s, "pfn") == 0)
    *ot = globus_rls_obj_lrc_pfn;
  else {
    fprintf(stderr, "Unknown object type %s: should be lfn or pfn\n", s);
    return 0;
  }
  return 1;
}
