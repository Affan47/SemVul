_endPaint()
{
	if (m_CairoCreated)
		cairo_destroy (m_cr);
	m_cr = NULL;

	m_Painting = false;
	m_CairoCreated = false;

	GR_CairoGraphics::_endPaint();
}
