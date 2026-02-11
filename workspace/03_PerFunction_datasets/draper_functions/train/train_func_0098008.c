findPointCoords(UT_uint32 iOffset, UT_sint32& x, UT_sint32& y, UT_sint32& x2, UT_sint32& y2, UT_sint32& height, bool& bDirection)
{

	UT_sint32 xoff;
	UT_sint32 yoff;
	UT_sint32 xoff2;
	UT_sint32 yoff2;

	UT_ASSERT(getLine());
	if(getLine()->getY() == -2000000)
	{

	}
	getLine()->getOffsets(this, xoff, yoff);

	fp_Run * pRun = 0;
	UT_sint32 iNextDir = getVisDirection();

	if (iOffset == (getBlockOffset() + getLength()))
	{
	    pRun = getNextRun();
	    if(pRun)
	    {
	        pRun->getLine()->getOffsets(pRun, xoff2, yoff2);
	        iNextDir = pRun->getVisDirection();
	    }
	}

	UT_sint32 iDirection = getVisDirection();

    x = xoff;

	if(iDirection == UT_BIDI_LTR)
	{
		xxx_UT_DEBUGMSG(("iOffset %d, getBlockOffset() %d, getLength() %d\n", iOffset,getBlockOffset(),getLength()));
		if(iOffset != getBlockOffset())
		{


			x += getWidth();
		}
	}
	else
	{
		if(iOffset == getBlockOffset())
		{
		    x += getWidth();
		}
	}


	if(pRun && (iNextDir != iDirection))
	{
	    x2 = (iNextDir == UT_BIDI_LTR) ?  xoff + pRun->getWidth() : xoff2;
	    y2 = yoff2;
	}
	else
	{
	    x2 = x;
	    y2 = yoff;
	}

	bDirection = (iDirection != UT_BIDI_LTR);
	y = yoff;
	height = getHeight();
}
