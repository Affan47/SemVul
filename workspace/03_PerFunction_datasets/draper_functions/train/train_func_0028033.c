getParamString() const {
	return QString("ResizeNoteCommand ")
		+ BaseCommand::getParamString()
		+ QString(" id:%1 oldsz:%2 %3 newsz:%4 %5")
			.arg(m_itemID).arg(m_oldSize.width()).arg(m_oldSize.height()).arg(m_newSize.width()).arg(m_newSize.height());

}
