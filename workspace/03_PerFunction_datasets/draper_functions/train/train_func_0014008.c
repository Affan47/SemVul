gistPopItupFromNodeBuffer(GISTBuildBuffers *gfbb, GISTNodeBuffer *nodeBuffer,
						  IndexTuple *itup)
{


	if (nodeBuffer->blocksCount <= 0)
		return false;


	if (!nodeBuffer->pageBuffer)
		gistLoadNodeBuffer(gfbb, nodeBuffer);


	gistGetItupFromPage(nodeBuffer->pageBuffer, itup);


	if (PAGE_IS_EMPTY(nodeBuffer->pageBuffer))
	{
		BlockNumber prevblkno;


		nodeBuffer->blocksCount--;


		prevblkno = nodeBuffer->pageBuffer->prev;
		if (prevblkno != InvalidBlockNumber)
		{

			Assert(nodeBuffer->blocksCount > 0);
			ReadTempFileBlock(gfbb->pfile, prevblkno, nodeBuffer->pageBuffer);


			gistBuffersReleaseBlock(gfbb, prevblkno);
		}
		else
		{

			Assert(nodeBuffer->blocksCount == 0);
			pfree(nodeBuffer->pageBuffer);
			nodeBuffer->pageBuffer = NULL;
		}
	}
	return true;
}
