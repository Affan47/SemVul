getTextBetweenPos(PT_DocPosition pos1, PT_DocPosition pos2) const
{
	UT_return_val_if_fail(pos2 > pos1, NULL);

	UT_GrowBuf buffer;

	UT_uint32 iLength = pos2 - pos1;

	PT_DocPosition curPos = pos1;


	const fl_BlockLayout * pBlock = m_pLayout->findBlockAtPosition(curPos);

	UT_UCSChar * bufferRet = new UT_UCSChar[iLength+1];

	UT_ASSERT(bufferRet);
	if(!bufferRet)
		return NULL;

	UT_UCSChar * buff_ptr = bufferRet;

	while(pBlock && curPos < pos2)
	{
		buffer.truncate(0);
		pBlock->getBlockBuf(&buffer);

		if (curPos < pBlock->getPosition(FALSE)) {
			curPos = pBlock->getPosition(FALSE);
		}
		PT_DocPosition offset = curPos - pBlock->getPosition(false);
		UT_uint32 iLenToCopy = UT_MIN(pos2 - curPos, buffer.getLength() - offset);
		if(curPos < pos2 && (curPos < pBlock->getPosition(false) + pBlock->getLength()))
		{
			memmove(buff_ptr, buffer.getPointer(offset), iLenToCopy * sizeof(UT_UCSChar));
			offset	 += iLenToCopy;
			buff_ptr += iLenToCopy;
			curPos	 += iLenToCopy;
			if (curPos < pos2)
			{
				*buff_ptr++ = '\n';
				curPos++;
			}
		}

		pBlock = static_cast<fl_BlockLayout *>(pBlock->getNextBlockInDocument());
	}

	UT_ASSERT(curPos == pos2);
	*buff_ptr = 0;
	return bufferRet;
}
