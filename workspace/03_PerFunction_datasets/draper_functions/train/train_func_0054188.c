mdopen(SMgrRelation reln, ForkNumber forknum, ExtensionBehavior behavior)
{
	MdfdVec    *mdfd;
	char	   *path;
	File		fd;


	if (reln->md_fd[forknum])
		return reln->md_fd[forknum];

	path = relpath(reln->smgr_rnode, forknum);

	fd = PathNameOpenFile(path, O_RDWR | PG_BINARY, 0600);

	if (fd < 0)
	{


		if (IsBootstrapProcessingMode())
			fd = PathNameOpenFile(path, O_RDWR | O_CREAT | O_EXCL | PG_BINARY, 0600);
		if (fd < 0)
		{
			if (behavior == EXTENSION_RETURN_NULL &&
				FILE_POSSIBLY_DELETED(errno))
			{
				pfree(path);
				return NULL;
			}
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not open file \"%s\": %m", path)));
		}
	}

	pfree(path);

	if (reln->smgr_transient)
		FileSetTransient(fd);

	reln->md_fd[forknum] = mdfd = _fdvec_alloc();

	mdfd->mdfd_vfd = fd;
	mdfd->mdfd_segno = 0;
	mdfd->mdfd_chain = NULL;
	Assert(_mdnblocks(reln, forknum, mdfd) <= ((BlockNumber) RELSEG_SIZE));

	return mdfd;
}
