_lookupLocalProperties()
{
	const PP_AttrProp * pSpanAP = NULL;
	const PP_AttrProp * pBlockAP = NULL;
	const PP_AttrProp * pSectionAP = NULL;

	getBlockAP(pBlockAP);

	if(!getBlock()->isContainedByTOC())
	{
		getSpanAP(pSpanAP);
	}

	_lookupProperties(pSpanAP, pBlockAP, pSectionAP,getGraphics());
}
