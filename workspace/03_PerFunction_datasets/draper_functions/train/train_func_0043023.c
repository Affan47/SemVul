RecreateCanvas()
{
	int x = GetSize().GetWidth();
	int y = GetSize().GetHeight();

	if ((x < 1) || (y < 1))
		return;

 	m_CanvasBitmap.Create(x, y);
	m_CanvasDC.SelectObject(m_CanvasBitmap);
}
