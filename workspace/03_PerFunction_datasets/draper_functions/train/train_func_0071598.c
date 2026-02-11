lineSpacingChanged(int index)
{
	switch (index) {
	case 0:
		m_line_spacing->setValue(100);
		m_line_spacing->setEnabled(false);
		break;

	case 1:
		m_line_spacing->setValue(150);
		m_line_spacing->setEnabled(false);
		break;

	case 2:
		m_line_spacing->setValue(200);
		m_line_spacing->setEnabled(false);
		break;

	default:
		m_line_spacing->setEnabled(true);
		break;
	}
}
