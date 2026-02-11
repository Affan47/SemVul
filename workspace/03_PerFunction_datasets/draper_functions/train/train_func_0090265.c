cleanup_interp_data(ClientData clientData, Tcl_Interp *interp)
{
  id_info *info;
  Tcl_HashEntry *entry;

  my_log(lexpos(), "cleaning up interp %x", interp);
  entry = Tcl_FindHashEntry(&interp_hash, (char *)interp);
  if (entry != NULL) {
    info = (id_info *)Tcl_GetHashValue(entry);
    id_info_free(info);
    Tcl_DeleteHashEntry(entry);
  }
}
