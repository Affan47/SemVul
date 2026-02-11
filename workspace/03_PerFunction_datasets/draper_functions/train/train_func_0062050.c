ResourceOwnerEnlargeFiles(ResourceOwner owner)
{
	int			newmax;

	if (owner->nfiles < owner->maxfiles)
		return;

	if (owner->files == NULL)
	{
		newmax = 16;
		owner->files = (File *)
			MemoryContextAlloc(TopMemoryContext, newmax * sizeof(File));
		owner->maxfiles = newmax;
	}
	else
	{
		newmax = owner->maxfiles * 2;
		owner->files = (File *)
			repalloc(owner->files, newmax * sizeof(File));
		owner->maxfiles = newmax;
	}
}
