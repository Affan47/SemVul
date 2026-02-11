slot_game_selected(int index)
{
	if(index>=m_pdn->count()) {
		qDebug() << __PRETTY_FUNCTION__ << "Index" << index
			<< "out of range >=" << m_pdn->count();
		return;
	}

	m_game = m_pdn->game(index);
	m_movelist->clear();

	QTreeWidgetItem* root = new QTreeWidgetItem(m_movelist);
	for(int i=0; i<m_game->movesCount(); ++i) {
		PdnMove* m = m_game->getMove(i);

		appendMove(m->m_first, m->m_comfirst);
		if(m->m_second.length())
			appendMove(m->m_second, m->m_comsecond);
	}

	setTag(PdnGame::Site,	m_game->get(PdnGame::Site));
	setTag(PdnGame::Black,	m_game->get(PdnGame::Black));
	setTag(PdnGame::White,	m_game->get(PdnGame::White));
	setTag(PdnGame::Result,	m_game->get(PdnGame::Result));
	setTag(PdnGame::Date,	m_game->get(PdnGame::Date));
	setTag(PdnGame::Site,	m_game->get(PdnGame::Site));
	setTag(PdnGame::Type,	m_game->get(PdnGame::Type));
	setTag(PdnGame::Round,	m_game->get(PdnGame::Round));
	setTag(PdnGame::Event,	m_game->get(PdnGame::Event));


	if(m_paused && !m_freeplace) {
		emit previewGame(m_game->get(PdnGame::Type).toInt());
	}

	m_movelist->setCurrentItem(root);
	slot_move(root, 0);
}
