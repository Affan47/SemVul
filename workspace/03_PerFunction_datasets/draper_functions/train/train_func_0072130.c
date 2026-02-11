getParamString() const {

	return QString("ResizeBoardCommand ")
		+ BaseCommand::getParamString() +
		QString(" id:%1 ow:%2 oh:%3 nw:%4 nh:%5")
		.arg(m_itemID)
		.arg(m_oldWidth)
		.arg(m_oldHeight)
		.arg(m_newWidth)
		.arg(m_newHeight);
}
