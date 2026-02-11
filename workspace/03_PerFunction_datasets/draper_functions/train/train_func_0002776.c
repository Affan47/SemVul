m_reply(struct Luser *lptr, struct NickInfo *nptr, int ac, char **av)

{
	struct MemoInfo *from;
	struct Memo *memoptr;
	struct NickInfo *master,
				*realptr;
	char memotext[MAXLINE + 1];
	int index, ii;

	if (!nptr)
		return;

	if (ac < 3)
{
		notice(n_MemoServ, lptr->nick, "Syntax: REPLY <index> <text>");
		notice(n_MemoServ, lptr->nick, ERR_MORE_INFO, n_MemoServ, "REPLY");
		return;
	}

	if (!(from = FindMemoList(nptr->nick)))
	{
		notice(n_MemoServ, lptr->nick, "You have no recorded memos");
		return;
	}

	index = IsNum(av[1]);
	if (!index || (index > from->memocnt))
	{
		notice(n_MemoServ, lptr->nick, "[\002%s\002] is an invalid index",
		       av[1]);
		return;
	}

	master = realptr = NULL;
	for (memoptr = from->memos; memoptr; memoptr = memoptr->next)
	{
		if (memoptr->index == index)
		{
			if (!(realptr = FindNick(memoptr->sender)))
			{
				notice(n_MemoServ, lptr->nick, ERR_NOT_REGGED, av[2]);
				return;
			}

			master = GetMaster(realptr);
			assert(master != 0);

			if (!(master->flags & NS_MEMOS))
			{
				notice(n_MemoServ, lptr->nick,
				       "[\002%s\002] is rejecting all memos",
				       master->nick);
				return;
			}

			break;
		}
	}

	if (!master || !realptr)
		return;

	ircsprintf(memotext, "[Re]: %s", av[2]);
	ii = 3;
	while (ii < ac)
	{
		strlcat(memotext, " ", sizeof(memotext));
		strlcat(memotext, av[ii], sizeof(memotext));
		ii++;
	}

	index = StoreMemo(master->nick, memotext, lptr);

	if (index)
	{
		notice(n_MemoServ, lptr->nick,
		       "Memo has been recorded for [\002%s\002]",
		       master->nick);
		memoptr->flags |= MS_REPLIED;


		if ((master->flags & NS_MEMONOTIFY) &&
		        (realptr->flags & NS_IDENTIFIED) &&
		        FindClient(realptr->nick))
		{
			notice(n_MemoServ, realptr->nick,
			       "You have a new memo from \002%s\002 (#%d)",
			       lptr->nick, index);
			notice(n_MemoServ, realptr->nick,
			       "Type \002/MSG %s READ %d\002 to read it",
			       n_MemoServ, index);
		}
	}
}
