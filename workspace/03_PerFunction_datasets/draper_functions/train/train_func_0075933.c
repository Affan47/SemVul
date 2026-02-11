register_dirty_segment(SMgrRelation reln, MdfdVec *seg)
{
	if (pendingOpsTable)
	{

		RememberFsyncRequest(reln->smgr_rnode, seg->mdfd_segno);
	}
	else
	{
		if (ForwardFsyncRequest(reln->smgr_rnode, seg->mdfd_segno))
			return;

		if (FileSync(seg->mdfd_vfd) < 0)
			ereport(ERROR,
					(errcode_for_file_access(),
				errmsg("could not fsync segment %u of relation %u/%u/%u: %m",
					   seg->mdfd_segno,
					   reln->smgr_rnode.spcNode,
					   reln->smgr_rnode.dbNode,
					   reln->smgr_rnode.relNode)));
	}
}
