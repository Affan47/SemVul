clearScreenFromRunToEnd(UT_uint32 runIndex)
{
	xxx_UT_DEBUGMSG(("Clear 2 from run %d to end line %x \n",runIndex,this));
	if(getBlock()->isHdrFtr())
	{
		return;
	}

	_doClearScreenFromRunToEnd((UT_sint32)runIndex);
}
