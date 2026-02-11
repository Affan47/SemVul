layout(void)
{
	if(isThisBroken())
	{
		UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
		return;
	}
	xxx_UT_DEBUGMSG(("Doing Table layout %x \n",this));

#if BENCHLAYOUT
	printf("Doing Table layout \n");
	timespec t1;
	clock_gettime(CLOCK_REALTIME, &t1);
#endif

	fl_TableLayout * pTL = static_cast<fl_TableLayout *>(getSectionLayout());
	if (!pTL->isInitialLayoutCompleted())
	{
		resize(m_iRows,m_iCols);
	}
	static fp_Requisition requisition;
	static fp_Allocation alloc;
	sizeRequest(&requisition);
	setX(m_iBorderWidth);
	alloc.x = getX();
	alloc.y = getY();
	alloc.width = getWidth();
	alloc.height = requisition.height;
	sizeAllocate(&alloc);
	setToAllocation();
#if BENCHLAYOUT
	timespec t2;
	clock_gettime(CLOCK_REALTIME, &t2);
	double millidiff = (t2.tv_sec-t1.tv_sec)*1e3 + (t2.tv_nsec-t1.tv_nsec)/1e6;
	printf("Layout TIME: %lf milliseconds\n", millidiff);
#endif
}
