getLeftTopOffsets(UT_sint32 & xoff, UT_sint32 & yoff) const
{
	fp_TableContainer * pTab = static_cast<fp_TableContainer *>(getContainer());
	UT_return_if_fail(pTab);
	xoff = -static_cast<UT_sint32>(pTab->getNthCol(getLeftAttach())->spacing);
	yoff = m_iTopY - getY();
}
