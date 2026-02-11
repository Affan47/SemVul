findWhereSimilarityResumes(PT_DocPosition &pos, UT_sint32 &iOffset2,
											 UT_uint32 & iKnownLength,
											 const PD_Document &d) const
{
	UT_return_val_if_fail(m_pPieceTable || d.m_pPieceTable, true);


	PD_DocIterator t1(*this, pos);
	PD_DocIterator t2(d, pos + iOffset2);


	UT_sint32 iTry = 128;
	UT_sint32 iMinOverlap = 3;
	UT_sint32 iStep = 128;
	UT_sint32 i = 0;

	UT_uint32 iFoundPos1 = 0;
	UT_uint32 iFoundPos2 = 0;
	UT_sint32 iFoundOffset1 = 0;
	UT_sint32 iFoundOffset2 = 0;

	for(i = iTry; i >= iMinOverlap; i -= iStep)
	{
		UT_uint32 pos1 = t1.getPosition();
		UT_uint32 pos2 = t2.getPosition();

		UT_uint32 iPos = t2.find(t1,i,true);

		if(t2.getStatus() == UTIter_OK)
		{

			iFoundPos1 = pos1;
			iFoundOffset1 = iPos - iFoundPos1;
			break;
		}
		else
		{

			t2.setPosition(pos2);
			t1.setPosition(pos1);

			if(iStep > 1)
				iStep /= 2;
		}
	}


	UT_sint32 iLen1 = i >= iMinOverlap ? i : 0;

	if(i == iTry)
	{

		pos = iFoundPos1;
		iOffset2 = iFoundOffset1;
		iKnownLength = iTry;
		return true;
	}


	t2.setPosition(pos);
	t1.setPosition(pos + iOffset2);
	iStep = 128;

	for(i = iTry; i >= iMinOverlap; i -= iStep)
	{
		UT_uint32 pos1 = t1.getPosition();
		UT_uint32 pos2 = t2.getPosition();

		UT_uint32 iPos = t1.find(t2,i,true);

		if(t1.getStatus() == UTIter_OK)
		{

			iFoundPos2 = iPos;
			iFoundOffset2 = pos2 - iFoundPos2;
			break;
		}
		else
		{

			t2.setPosition(pos2);
			t1.setPosition(pos1);

			if(iStep > 1)
				iStep /= 2;
		}
	}

	UT_sint32 iLen2 = i >= iMinOverlap ? i : 0;

	if( !iLen1 && !iLen2)
		return false;


	if(iLen1 >= iLen2)
	{
		pos = iFoundPos1;
		iOffset2 = iFoundOffset1;
		iKnownLength = iLen1;
	}
	else
	{
		pos = iFoundPos2;
		iOffset2 = iFoundOffset2;
		iKnownLength = iLen2;
	}

	return true;
}
