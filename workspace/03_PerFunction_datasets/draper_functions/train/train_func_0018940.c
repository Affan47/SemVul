_createPreviewFromGC(GR_Graphics * gc,
						 UT_uint32 width,
						 UT_uint32 height)
{
	UT_return_if_fail (gc);
	m_preview = new AP_Preview_PageNumbers (gc);
	UT_return_if_fail (m_preview);

	m_preview->setWindowSize (width, height);
}
