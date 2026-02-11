ReadDataFromArchive(ArchiveHandle *AH, int compression, ReadFunc readF)
{
	CompressionAlgorithm alg;

	ParseCompressionOption(compression, &alg, NULL);

	if (alg == COMPR_ALG_NONE)
		ReadDataFromArchiveNone(AH, readF);
	if (alg == COMPR_ALG_LIBZ)
	{
#ifdef HAVE_LIBZ
		ReadDataFromArchiveZlib(AH, readF);
#else
		die_horribly(NULL, modulename, "not built with zlib support\n");
#endif
	}
}
