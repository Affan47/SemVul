getNextVisual()
{
	if(!getLine())
		return NULL;

	UT_uint32 iIndxVis = getLine()->getVisIndx(this);

	return getLine()->getRunAtVisPos(iIndxVis + 1);
}
