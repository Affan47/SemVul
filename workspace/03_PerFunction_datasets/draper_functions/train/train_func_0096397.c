procmime_get_first_text_content(MsgInfo *msginfo)
{
	FILE *outfp = NULL;
	MimeInfo *mimeinfo, *partinfo;
	gboolean empty_ok = FALSE, short_scan = TRUE;

    	cm_return_val_if_fail(msginfo != NULL, NULL);


scan_again:
	if (short_scan)
		mimeinfo = procmime_scan_message_short(msginfo);
	else
		mimeinfo = procmime_scan_message(msginfo);
	if (!mimeinfo) return NULL;

	partinfo = mimeinfo;
	while (partinfo && (partinfo->type != MIMETYPE_TEXT ||
	       (partinfo->length == 0 && !empty_ok))) {
		partinfo = procmime_mimeinfo_next(partinfo);
	}
	if (partinfo)
		outfp = procmime_get_text_content(partinfo);
	else if (!empty_ok && short_scan) {


		short_scan = FALSE;
		procmime_mimeinfo_free_all(mimeinfo);
		goto scan_again;
	} else if (!empty_ok && !short_scan) {


		empty_ok = TRUE;
		procmime_mimeinfo_free_all(mimeinfo);
		goto scan_again;
	}
	procmime_mimeinfo_free_all(mimeinfo);


	return outfp;
}
