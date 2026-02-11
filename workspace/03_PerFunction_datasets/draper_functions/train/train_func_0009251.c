procmsg_msginfo_copy(MsgInfo *msginfo)
{
	MsgInfo *newmsginfo;
        GSList *refs;

	if (msginfo == NULL) return NULL;

	newmsginfo = g_new0(MsgInfo, 1);

	newmsginfo->refcnt = 1;

#define MEMBCOPY(mmb)	newmsginfo->mmb = msginfo->mmb
#define MEMBDUP(mmb)	newmsginfo->mmb = msginfo->mmb ? \
			g_strdup(msginfo->mmb) : NULL

	MEMBCOPY(msgnum);
	MEMBCOPY(size);
	MEMBCOPY(mtime);
	MEMBCOPY(date_t);

	MEMBCOPY(flags);

	MEMBDUP(fromname);

	MEMBDUP(date);
	MEMBDUP(from);
	MEMBDUP(to);
	MEMBDUP(cc);
	MEMBDUP(newsgroups);
	MEMBDUP(subject);
	MEMBDUP(msgid);
	MEMBDUP(inreplyto);
	MEMBDUP(xref);

	MEMBCOPY(folder);
	MEMBCOPY(to_folder);

	if (msginfo->extradata) {
		newmsginfo->extradata = g_new0(MsgInfoExtraData, 1);
		MEMBDUP(extradata->face);
		MEMBDUP(extradata->xface);
		MEMBDUP(extradata->dispositionnotificationto);
		MEMBDUP(extradata->returnreceiptto);
		MEMBDUP(extradata->partial_recv);
		MEMBDUP(extradata->account_server);
		MEMBDUP(extradata->account_login);
		MEMBDUP(extradata->list_post);
		MEMBDUP(extradata->list_subscribe);
		MEMBDUP(extradata->list_unsubscribe);
		MEMBDUP(extradata->list_help);
		MEMBDUP(extradata->list_archive);
		MEMBDUP(extradata->list_owner);
	}

        refs = msginfo->references;
        for (refs = msginfo->references; refs != NULL; refs = refs->next) {
                newmsginfo->references = g_slist_prepend
                        (newmsginfo->references, g_strdup(refs->data));
        }
        newmsginfo->references = g_slist_reverse(newmsginfo->references);

	MEMBCOPY(score);
	MEMBDUP(plaintext_file);

	return newmsginfo;
}
