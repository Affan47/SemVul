_StartBlob(ArchiveHandle *AH, TocEntry *te, Oid oid)
{
	lclContext *ctx = (lclContext *) AH->formatData;

	if (oid == 0)
		die_horribly(AH, modulename, "invalid OID for large object\n");

	WriteInt(AH, oid);

	ctx->cs = AllocateCompressor(AH->compression, _CustomWriteFunc);
}
