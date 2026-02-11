PrescanPreparedTransactions(void)
{
	TransactionId origNextXid = ShmemVariableCache->nextXid;
	TransactionId result = origNextXid;
	DIR		   *cldir;
	struct dirent *clde;

	cldir = AllocateDir(TWOPHASE_DIR);
	while ((clde = ReadDir(cldir, TWOPHASE_DIR)) != NULL)
	{
		if (strlen(clde->d_name) == 8 &&
			strspn(clde->d_name, "0123456789ABCDEF") == 8)
		{
			TransactionId xid;
			char	   *buf;
			TwoPhaseFileHeader *hdr;
			TransactionId *subxids;
			int			i;

			xid = (TransactionId) strtoul(clde->d_name, NULL, 16);


			if (TransactionIdFollowsOrEquals(xid, origNextXid))
			{
				ereport(WARNING,
						(errmsg("removing future two-phase state file \"%s\"",
								clde->d_name)));
				RemoveTwoPhaseFile(xid, true);
				continue;
			}


			buf = ReadTwoPhaseFile(xid);
			if (buf == NULL)
			{
				ereport(WARNING,
						(errmsg("removing corrupt two-phase state file \"%s\"",
								clde->d_name)));
				RemoveTwoPhaseFile(xid, true);
				continue;
			}


			hdr = (TwoPhaseFileHeader *) buf;
			if (!TransactionIdEquals(hdr->xid, xid))
			{
				ereport(WARNING,
						(errmsg("removing corrupt two-phase state file \"%s\"",
								clde->d_name)));
				RemoveTwoPhaseFile(xid, true);
				pfree(buf);
				continue;
			}


			if (TransactionIdPrecedes(xid, result))
				result = xid;


			subxids = (TransactionId *)
				(buf + MAXALIGN(sizeof(TwoPhaseFileHeader)));
			for (i = 0; i < hdr->nsubxacts; i++)
			{
				TransactionId subxid = subxids[i];

				Assert(TransactionIdFollows(subxid, xid));
				if (TransactionIdFollowsOrEquals(subxid,
												 ShmemVariableCache->nextXid))
				{
					ShmemVariableCache->nextXid = subxid;
					TransactionIdAdvance(ShmemVariableCache->nextXid);
				}
			}

			pfree(buf);
		}
	}
	FreeDir(cldir);

	return result;
}
