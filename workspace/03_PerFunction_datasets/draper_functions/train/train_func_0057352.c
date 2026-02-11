getParamString() const {
	return QString("AddSubpartCommand ")
		+ BaseCommand::getParamString() +
		QString(" id:%1 subpart id:%2")
		.arg(m_itemID)
		.arg(m_subpartItemID)
		;
}
