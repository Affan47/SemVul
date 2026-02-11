doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx)
{
	UT_UNUSED(pcrx);
	UT_ASSERT(pcrx->getType()==PX_ChangeRecord::PXT_DeleteStrux);
#if 0
	fp_FrameContainer * pFrameC = getFirstContainer();
	if(pFrameC && pFrameC->getPage())
	{
		pFrameC->getPage()->markDirtyOverlappingRuns(pFrameC);
	}
#endif
	fp_FrameContainer * pFrameC = static_cast<fp_FrameContainer *>(getFirstContainer());
	UT_GenericVector<fl_BlockLayout *> vecBlocks;
	pFrameC->getBlocksAroundFrame(vecBlocks);
	UT_sint32 i = 0;
	for(i=0; i< vecBlocks.getItemCount();i++)
	{
	  fl_BlockLayout * pBL = vecBlocks.getNthItem(i);
	  pBL->collapse();
	  xxx_UT_DEBUGMSG(("Collapse block %x \n",pBL));
	}


	collapse();
	myContainingLayout()->remove(this);
	UT_DEBUGMSG(("Unlinking frame Layout %p \n",this));


	fl_ContainerLayout * pCL = getParentContainer();
	fl_BlockLayout * pBL = NULL;
	if(pCL)
	{
		if(!pCL->removeFrame(this))
		{
			UT_DEBUGMSG(("Whoops! Frame not found in container %p\n",pCL));
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		}
	}
	for(i=0; i< vecBlocks.getItemCount();i++)
	{
	  pBL = vecBlocks.getNthItem(i);
	  pBL->format();
	  xxx_UT_DEBUGMSG(("Format block %p\n",pBL));
	}

	delete this;

	return true;
}
