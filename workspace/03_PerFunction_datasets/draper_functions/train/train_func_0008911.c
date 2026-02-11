getPoint(GLEJustify just) {
	switch (just) {
		case GLEJustifyRC:
			return GLEPoint(m_Center.getX()+m_Rx, m_Center.getY());
		case GLEJustifyTL:
			return GLEPoint(m_Center.getX()-m_Rx, m_Center.getY()+m_Ry);
		case GLEJustifyBR:
			return GLEPoint(m_Center.getX()+m_Rx, m_Center.getY()-m_Ry);
		default:
			break;
	}
	return GLEPoint();
}
