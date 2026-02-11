_updatePreview(AP_Dialog_PageNumbers::tAlign align,
					   AP_Dialog_PageNumbers::tControl ctrl)
{
	UT_return_if_fail (m_preview);
	m_preview->setHdrFtr (ctrl);
	m_preview->setAlign (align);
	m_preview->queueDraw ();
}
