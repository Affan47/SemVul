undeletecmd(void *v)
{
	int *msgvec = v;
	struct message *mp;
	int *ip;

	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
		setdot(mp);
		if (mp->m_flag & (MDELETED|MSAVED))
			mp->m_flag &= ~(MDELETED|MSAVED);
		else
			mp->m_flag &= ~MDELETED;
		if (mb.mb_type == MB_IMAP || mb.mb_type == MB_CACHE)
			imap_undelete(mp, *ip);
	}
	return 0;
}
