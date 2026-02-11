make_dir(const MkdInfo *mdi)
{
	const gchar	*text;
	GFile		*dest;
	gboolean	ok = FALSE;
	GError		*err = NULL;

	if(mdi == NULL)
		return FALSE;
	text = gtk_entry_get_text(GTK_ENTRY(mdi->entry));
	if(*text == '\0')
		return FALSE;
	if(mdi->src->dir.root == NULL)
		return FALSE;

	err_clear(mdi->src->main);
	if((dest = g_file_get_child_for_display_name(mdi->src->dir.root, text, &err)) != NULL)
	{
		ovw_overwrite_begin(mdi->src->main, _("\"%s\" Already Exists - Proceed With MkDir?"), 0UL);
		switch(ovw_overwrite_unary_file(mdi->src, dest))
		{
		case OVW_SKIP:
		case OVW_CANCEL:
			ok = FALSE;
			break;
		case OVW_PROCEED:
			ok = TRUE;
			break;
		case OVW_PROCEED_FILE:
			ok = del_delete_gfile(mdi->src->main, dest, FALSE, &err);
			break;
		case OVW_PROCEED_DIR:
			ok = FALSE;
			break;
		}
		ovw_overwrite_end(mdi->src->main);
		if(ok)
		{
			ok = g_file_make_directory(dest, NULL, &err);
			if(ok)
			{
				gchar	*pn = g_file_get_parse_name(dest);

				if(mkdir_options.cd_new)
					ok = csq_execute_format(mdi->src->main, "DirEnter 'dir=%s'", pn);
				else if(mkdir_options.focus_new)
					ok = csq_execute_format(mdi->src->main, "DpGotoRow focus=%s nocase=no 're=%s'", mkdir_options.focus_new ? "yes" : "no", pn);
				if(!mkdir_options.cd_new)
					dp_rescan_post_cmd(mdi->src);
				g_free(pn);
			}
		}
		g_object_unref(dest);
	}
	if(err != NULL)
		err_set_gerror(mdi->src->main, &err, text, NULL);

	return ok;
}
