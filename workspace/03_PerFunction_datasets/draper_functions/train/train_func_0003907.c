repalloc(void *pointer, Size size)
{
	StandardChunkHeader *header;


	Assert(pointer != NULL);
	Assert(pointer == (void *) MAXALIGN(pointer));


	header = (StandardChunkHeader *)
		((char *) pointer - STANDARDCHUNKHEADERSIZE);

	AssertArg(MemoryContextIsValid(header->context));

	if (!AllocSizeIsValid(size))
		elog(ERROR, "invalid memory alloc request size %lu",
			 (unsigned long) size);


	Assert(!header->context->isReset);

	return (*header->context->methods->realloc) (header->context,
												 pointer, size);
}
