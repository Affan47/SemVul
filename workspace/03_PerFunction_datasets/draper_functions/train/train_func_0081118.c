mdclose(SMgrRelation reln, ForkNumber forknum)
{
	MdfdVec    *v = reln->md_fd[forknum];


	if (v == NULL)
		return;

	reln->md_fd[forknum] = NULL;

	while (v != NULL)
	{
		MdfdVec    *ov = v;


		if (v->mdfd_vfd >= 0)
			FileClose(v->mdfd_vfd);

		v = v->mdfd_chain;
		pfree(ov);
	}
}
