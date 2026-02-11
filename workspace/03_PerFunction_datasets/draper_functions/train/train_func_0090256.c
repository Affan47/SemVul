simpleRecalcWidth(UT_sint32 iLength)
{

	if(iLength == Calculate_full_width)
	{
		iLength = getLength();
	}
	UT_ASSERT(iLength >= 0);

	UT_ASSERT(static_cast<UT_uint32>(iLength) <= getLength());
	if(static_cast<UT_uint32>(iLength) > getLength())
		iLength = static_cast<UT_sint32>(getLength());

	if (iLength == 0)
		return 0;

	_refreshDrawBuffer();
	UT_return_val_if_fail(m_pRenderInfo,0);

	m_pRenderInfo->m_iOffset = 0;
	m_pRenderInfo->m_iLength = getLength();
	UT_sint32 iWidth = getGraphics()->getTextWidth(*m_pRenderInfo);

	return iWidth;
}
