gistGetNodeBuffer(GISTBuildBuffers *gfbb, GISTSTATE *giststate,
				  BlockNumber nodeBlocknum, int level)
{
	GISTNodeBuffer *nodeBuffer;
	bool		found;


	nodeBuffer = (GISTNodeBuffer *) hash_search(gfbb->nodeBuffersTab,
												(const void *) &nodeBlocknum,
												HASH_ENTER,
												&found);
	if (!found)
	{


		MemoryContext oldcxt = MemoryContextSwitchTo(gfbb->context);


		nodeBuffer->blocksCount = 0;
		nodeBuffer->pageBlocknum = InvalidBlockNumber;
		nodeBuffer->pageBuffer = NULL;
		nodeBuffer->queuedForEmptying = false;
		nodeBuffer->level = level;


		if (level >= gfbb->buffersOnLevelsLen)
		{
			int			i;

			gfbb->buffersOnLevels =
				(List **) repalloc(gfbb->buffersOnLevels,
								   (level + 1) * sizeof(List *));


			for (i = gfbb->buffersOnLevelsLen; i <= level; i++)
				gfbb->buffersOnLevels[i] = NIL;
			gfbb->buffersOnLevelsLen = level + 1;
		}


		gfbb->buffersOnLevels[level] = lcons(nodeBuffer,
											 gfbb->buffersOnLevels[level]);

		MemoryContextSwitchTo(oldcxt);
	}

	return nodeBuffer;
}
