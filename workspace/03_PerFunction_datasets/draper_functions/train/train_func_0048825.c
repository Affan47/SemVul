mdtruncate(SMgrRelation reln, ForkNumber forknum, BlockNumber nblocks,
		   bool isTemp)
{
	MdfdVec    *v;
	BlockNumber curnblk;
	BlockNumber priorblocks;


	curnblk = mdnblocks(reln, forknum);
	if (nblocks > curnblk)
	{

		if (InRecovery)
			return;
		ereport(ERROR,
				(errmsg("could not truncate file \"%s\" to %u blocks: it's only %u blocks now",
						relpath(reln->smgr_rnode, forknum),
						nblocks, curnblk)));
	}
	if (nblocks == curnblk)
		return;

	v = mdopen(reln, forknum, EXTENSION_FAIL);

	priorblocks = 0;
	while (v != NULL)
	{
		MdfdVec    *ov = v;

		if (priorblocks > nblocks)
		{


			if (FileTruncate(v->mdfd_vfd, 0) < 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not truncate file \"%s\": %m",
								FilePathName(v->mdfd_vfd))));

			if (!isTemp)
				register_dirty_segment(reln, forknum, v);
			v = v->mdfd_chain;
			Assert(ov != reln->md_fd[forknum]);

			pfree(ov);
		}
		else if (priorblocks + ((BlockNumber) RELSEG_SIZE) > nblocks)
		{


			BlockNumber lastsegblocks = nblocks - priorblocks;

			if (FileTruncate(v->mdfd_vfd, (off_t) lastsegblocks * BLCKSZ) < 0)
				ereport(ERROR,
						(errcode_for_file_access(),
					errmsg("could not truncate file \"%s\" to %u blocks: %m",
						   FilePathName(v->mdfd_vfd),
						   nblocks)));
			if (!isTemp)
				register_dirty_segment(reln, forknum, v);
			v = v->mdfd_chain;
			ov->mdfd_chain = NULL;
		}
		else
		{


			v = v->mdfd_chain;
		}
		priorblocks += RELSEG_SIZE;
	}
}
