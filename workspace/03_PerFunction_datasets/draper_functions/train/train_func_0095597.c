getParamString() const {
	return QString("MoveItemCommand ")
		+ BaseCommand::getParamString() +
		QString(" id:%1 old.x:%2 old.y:%3 old.px:%4 old.py:%5 new.x:%6 new.y:%7 new.px:%8 new.py:%9")
		.arg(m_itemID)
		.arg(m_old.loc().x())
		.arg(m_old.loc().y())
		.arg(m_old.line().p2().x())
		.arg(m_old.line().p2().y())
		.arg(m_new.loc().x())
		.arg(m_new.loc().y())
		.arg(m_new.line().p2().x())
		.arg(m_new.line().p2().y())
		;
}
