_createSymbolFromGC(GR_Graphics * gc,
												   UT_uint32 width, UT_uint32 height)
{
	UT_ASSERT(gc);
	DELETEP(m_DrawSymbol);
	m_DrawSymbol = new XAP_Draw_Symbol(gc);
	UT_ASSERT(m_DrawSymbol);
	m_DrawSymbol->setWindowSize(width, height);
}
