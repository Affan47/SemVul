rlink_put(char *vfs_uri, char *rname, char *buf)
{
  Parse_xml_error err;
  Vfs_handle *h;


  if (check_acl(buf, &err) == -1) {
	log_msg((LOG_ERROR_LEVEL, "Parse error: %s (Line %d, Character offset %d)",
			 err.mesg, err.line, err.pos));
	return(-1);
  }

  if (vfs_uri == NULL)
	vfs_uri = item_type;

  if ((h = vfs_open_any(vfs_uri)) == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Could not open Rlink from \"%s\"", vfs_uri));
	return(-1);
  }

  if (vfs_put(h, rname, (void *) buf, strlen(buf)) == -1) {
	log_msg((LOG_ERROR_LEVEL, "Could not put Rlink \"%s\" to \"%s\"",
			 vfs_uri, rname));
	vfs_close(h);
	return(-1);
  }

  if (vfs_close(h) == -1) {
	log_msg((LOG_ERROR_LEVEL, "Could not close Rlink \"%s\"", vfs_uri));
	return(-1);
  }

  return(0);
}
