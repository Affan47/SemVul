vfs_init_directive(Vfs_directive *ovd)
{
  Vfs_directive *vd;

  if (ovd == NULL)
	vd = ALLOC(Vfs_directive);
  else
	vd = ovd;

  vd->uri = NULL;
  vd->uri_str = NULL;
  vd->store_name = NULL;
  vd->item_type = NULL;
  vd->naming_context = NULL;
  vd->option_str = NULL;
  vd->path = NULL;
  vd->options = NULL;

  return(vd);
}
