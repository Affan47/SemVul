lookup_indexed_acl(char *item_type, char *path, Acl_rule **acl)
{
  int i, n;
  Acl_index *ad;
  Acl_map *am;

  if ((ad = get_acl_index(item_type)) == NULL) {
	fprintf(stderr, "Could not get ACL index\n");
	return(NULL);
  }

  n = dsvec_len(ad->acl_map);
  for (i = 0; i < n; i++) {
	am = (Acl_map *) dsvec_ptr_index(ad->acl_map, i);
	if (streq(am->path, path))
	  return(am);
  }

  return(NULL);
}
