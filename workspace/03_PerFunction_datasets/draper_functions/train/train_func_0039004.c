fill_search_preparse(struct searchinfo *p)
{
	switch (p->type) {
	case search_msgflag:
		{
			struct imapflags flags;

			memset(&flags, 0, sizeof(flags));
			p->ke=NULL;

			if (get_flagname(p->as, &flags) == 0)
			{
				p->bs=malloc(sizeof(flags));

				if (!p->bs)
					write_error_exit(0);

				memcpy(p->bs, &flags, sizeof(flags));
			}
		}
		break;

	case search_msgkeyword:
		p->ke=NULL;
		if (valid_keyword(p->as))
			p->ke=libmail_kweFind(current_maildir_info
					       .keywordList,
					       p->as, 0);
		break;
	default:
		break;
	}
}
