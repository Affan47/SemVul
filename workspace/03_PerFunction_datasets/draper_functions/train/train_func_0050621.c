PurgeMemos(struct MemoInfo *mptr)

{
	int ret;
	struct Memo *memoptr, *next;

	if (!mptr)
		return 0;

	ret = 0;
	for (memoptr = mptr->memos; memoptr; memoptr = next)
	{
		next = memoptr->next;

		if (memoptr->flags & MS_DELETE)
		{
			++ret;
			DeleteMemo(mptr, memoptr);
		}
	}

	mptr->memocnt -= ret;

	if (!mptr->memocnt)
	{


		DeleteMemoList(mptr);
		return (ret);
	}
	else if (ret)
	{
		int cnt;


		cnt = 0;
		for (memoptr = mptr->memos; memoptr; memoptr = memoptr->next)
		{
			if (memoptr->index != (cnt + 1))
				memoptr->index = cnt + 1;
			++cnt;
		}
	}

	return (ret);
}
