_drawPageBackground(void)
{

	GR_Painter painter(m_gc);
	painter.fillRect(*m_clrWhite, 0, 0, m_gc->tlu(getWindowWidth()), m_gc->tlu(getWindowHeight()));
}
