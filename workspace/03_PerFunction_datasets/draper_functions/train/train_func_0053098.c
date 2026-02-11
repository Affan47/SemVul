vlistHasTime(int vlistID)
{
  int varID;
  int hastime = FALSE;
  vlist_t *vlistptr;

  vlistptr = vlist_to_pointer(vlistID);

  vlist_check_ptr(__func__, vlistptr);

  for ( varID = 0; varID <  vlistptr->nvars; varID++ )
    if ( vlistptr->vars[varID].tsteptype != TSTEP_CONSTANT )
      {
        hastime = TRUE;
        break;
      }

  return (hastime);
}
