needsSpecialCaretPositioning(GR_RenderInfo &ri)
{


	GR_PangoRenderInfo & RI = (GR_PangoRenderInfo &)ri;
	if(RI.m_pText == NULL)
		return false;

	UT_TextIterator & text = static_cast<UT_TextIterator &>(*RI.m_pText);
	UT_uint32 origPos = text.getPosition();

	for(UT_sint32 i = 0; i < RI.m_iLength && text.getStatus() == UTIter_OK;
		++i, ++text)
	{
		UT_UCS4Char c = text.getChar();
		if(c != ' ' && c<256)
		{

			text.setPosition(origPos);
			return false;
		}
	}


	text.setPosition(origPos);
	return true;
}
