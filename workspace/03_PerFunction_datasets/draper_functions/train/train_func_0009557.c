_skipBlobs(ArchiveHandle *AH)
{
	Oid			oid;

	oid = ReadInt(AH);
	while (oid != 0)
	{
		_skipData(AH);
		oid = ReadInt(AH);
	}
}
