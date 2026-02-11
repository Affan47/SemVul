vfss_delete(Vfs_handle *handle, char *key, char **ermsg)
{

  if (vfs_delete(handle, key) == -1)
	return(-1);
  else {
	if (app_type == DACS_WEB_SERVICE)
	  printf("\nok\n");
  }

  return(0);
}
