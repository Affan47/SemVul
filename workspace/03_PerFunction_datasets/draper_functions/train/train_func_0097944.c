vlistChangeGridIndex(int vlistID, int index, int gridID)
{
  int gridIDold;
  int varID, nvars;
  vlist_t *vlistptr;

  vlistptr = vlist_to_pointer(vlistID);

  vlist_check_ptr(__func__, vlistptr);

  if ( reshGetStatus ( vlistID, &vlist_ops ) == CLOSED )
    {
      xwarning("%s", "Operation not executed." );
      return;
    }

  gridIDold = vlistptr->gridIDs[index];
  vlistptr->gridIDs[index] = gridID;

  nvars = vlistptr->nvars;
  for ( varID = 0; varID < nvars; varID++ )
    if ( vlistptr->vars[varID].gridID == gridIDold )
      vlistptr->vars[varID].gridID = gridID;
}
