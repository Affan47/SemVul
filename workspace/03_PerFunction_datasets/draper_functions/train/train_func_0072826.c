vlist_def_att(int indtype, int exdtype, int vlistID, int varID, const char *name, size_t len, size_t xsz, const void *xp)
{
  int status = CDI_NOERR;
  vlist_t *vlistptr;
  cdi_att_t *attp;
  cdi_atts_t *attsp;

  if ( len != 0 && xp == NULL )
    {
      return (CDI_EINVAL);
    }

  vlistptr = vlist_to_pointer(vlistID);

  attsp = get_attsp(vlistptr, varID);
  xassert(attsp != NULL);

  attp = find_att(attsp, name);
  if ( attp == NULL )
    attp = new_att(attsp, name);

  if ( attp != NULL )
    fill_att(attp, indtype, exdtype, len, xsz, xp);

  return (status);
}
