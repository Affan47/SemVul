ReadTwoPhaseFile(TransactionId xid)
{
	char		path[MAXPGPATH];
	char	   *buf;
	TwoPhaseFileHeader *hdr;
	int			fd;
	struct stat stat;
	uint32		crc_offset;
	pg_crc32	calc_crc,
				file_crc;

	TwoPhaseFilePath(path, xid);

	fd = BasicOpenFile(path, O_RDONLY | PG_BINARY, 0);
	if (fd < 0)
	{
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("could not open two-phase state file \"%s\": %m",
						path)));
		return NULL;
	}


	if (fstat(fd, &stat))
	{
		close(fd);
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("could not stat two-phase state file \"%s\": %m",
						path)));
		return NULL;
	}

	if (stat.st_size < (MAXALIGN(sizeof(TwoPhaseFileHeader)) +
						MAXALIGN(sizeof(TwoPhaseRecordOnDisk)) +
						sizeof(pg_crc32)) ||
		stat.st_size > MaxAllocSize)
	{
		close(fd);
		return NULL;
	}

	crc_offset = stat.st_size - sizeof(pg_crc32);
	if (crc_offset != MAXALIGN(crc_offset))
	{
		close(fd);
		return NULL;
	}


	buf = (char *) palloc(stat.st_size);

	if (read(fd, buf, stat.st_size) != stat.st_size)
	{
		close(fd);
		ereport(WARNING,
				(errcode_for_file_access(),
				 errmsg("could not read two-phase state file \"%s\": %m",
						path)));
		pfree(buf);
		return NULL;
	}

	close(fd);

	hdr = (TwoPhaseFileHeader *) buf;
	if (hdr->magic != TWOPHASE_MAGIC || hdr->total_len != stat.st_size)
	{
		pfree(buf);
		return NULL;
	}

	INIT_CRC32(calc_crc);
	COMP_CRC32(calc_crc, buf, crc_offset);
	FIN_CRC32(calc_crc);

	file_crc = *((pg_crc32 *) (buf + crc_offset));

	if (!EQ_CRC32(calc_crc, file_crc))
	{
		pfree(buf);
		return NULL;
	}

	return buf;
}
