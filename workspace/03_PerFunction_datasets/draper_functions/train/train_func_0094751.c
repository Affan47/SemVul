imapx_free_status (struct _status_info *sinfo)
{
	if (sinfo == NULL)
		return;

	switch (sinfo->condition) {
	case IMAPX_NEWNAME:
		g_free (sinfo->u.newname.oldname);
		g_free (sinfo->u.newname.newname);
		break;
	case IMAPX_COPYUID:
		g_ptr_array_free (sinfo->u.copyuid.uids, FALSE);
		g_ptr_array_free (sinfo->u.copyuid.copied_uids, FALSE);
		break;
	case IMAPX_CAPABILITY:
		if (sinfo->u.cinfo)
			imapx_free_capability (sinfo->u.cinfo);
		break;
	default:
		break;
	}

	g_free (sinfo->text);
	g_free (sinfo);
}
