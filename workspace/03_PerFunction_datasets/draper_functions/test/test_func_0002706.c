_createFontPreviewFromGC(GR_Graphics * gc,
													  UT_uint32 width,
													  UT_uint32 height)
{
	UT_ASSERT(gc);

	m_pFontPreview = new XAP_Preview_FontPreview(gc,m_sColorBackground.c_str());
	UT_return_if_fail(m_pFontPreview);

	m_pFontPreview->setWindowSize(width, height);
	m_pFontPreview->setVecProperties( & m_mapProps);
}
