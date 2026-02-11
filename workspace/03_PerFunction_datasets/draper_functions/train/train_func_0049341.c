vlistNrecs(int vlistID)
{
  int varID, nrecs = 0;
  vlist_t *vlistptr;

  vlistptr = vlist_to_pointer(vlistID);

  vlist_check_ptr(__func__, vlistptr);

  for ( varID = 0; varID < vlistptr->nvars; varID++ )
    nrecs +=  vlistptr->vars[varID].nlevs;

  return (nrecs);
}
