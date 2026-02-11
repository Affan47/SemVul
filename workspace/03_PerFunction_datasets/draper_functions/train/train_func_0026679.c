findNextLineInDocument(fp_Line* pLine) const
{
	if (pLine->getNext())
	{
		return static_cast<fp_Line *>(pLine->getNext());
	}

	if (getNext())
	{

		return static_cast<fp_Line *>(getNext()->getFirstContainer());
	}
	else
	{

		const fl_SectionLayout* pSL = static_cast<const fl_SectionLayout*>(m_pSectionLayout->getNext());

		if (!pSL)
		{

			return NULL;
		}


		UT_ASSERT_HARMLESS( pSL->getLastLayout() && pSL->getLastLayout()->getContainerType() == FL_CONTAINER_BLOCK );

		const fl_BlockLayout* pBlock = static_cast<const fl_BlockLayout*>(pSL->getFirstLayout());
		UT_return_val_if_fail(pBlock, NULL);
		return static_cast<fp_Line *>(pBlock->getFirstContainer());
	}

	UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
	return NULL;
}
