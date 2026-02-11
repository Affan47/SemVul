RestoringToDB(ArchiveHandle *AH)
{
	return (AH->ropt && AH->ropt->useDB && AH->connection);
}
