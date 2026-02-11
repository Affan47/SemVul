gistxlogFindPath(Relation index, gistIncompleteInsert *insert)
{
	GISTInsertStack *top;

	insert->pathlen = 0;
	insert->path = NULL;

	if ((top = gistFindPath(index, insert->origblkno)) != NULL)
	{
		int			i;
		GISTInsertStack *ptr;

		for (ptr = top; ptr; ptr = ptr->parent)
			insert->pathlen++;

		insert->path = (BlockNumber *) palloc(sizeof(BlockNumber) * insert->pathlen);

		i = 0;
		for (ptr = top; ptr; ptr = ptr->parent)
			insert->path[i++] = ptr->blkno;
	}
	else
		elog(ERROR, "lost parent for block %u", insert->origblkno);
}
