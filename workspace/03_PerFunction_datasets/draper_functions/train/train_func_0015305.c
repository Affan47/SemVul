_MasterStartParallelItem(ArchiveHandle *AH, TocEntry *te, T_Action act)
{


	static char buf[64];

	if (act == ACT_DUMP)
		snprintf(buf, sizeof(buf), "DUMP %d", te->dumpId);
	else if (act == ACT_RESTORE)
		snprintf(buf, sizeof(buf), "RESTORE %d", te->dumpId);

	return buf;
}
