displayBonus() {
	if (!items().contains(m_bonusItem)) {
		switch (m_game->getLevel()) {
			case 1:
				m_bonusItem->setElementId("bonus1");
				break;
			case 2:
				m_bonusItem->setElementId("bonus2");
				break;
			case 3:
				m_bonusItem->setElementId("bonus3");
				break;
			case 4:
				m_bonusItem->setElementId("bonus4");
				break;
			case 5:
				m_bonusItem->setElementId("bonus5");
				break;
			case 6:
				m_bonusItem->setElementId("bonus6");
				break;
			default:
				m_bonusItem->setElementId("bonus7");
				break;
		}
		m_bonusItem->update(m_game->getBonus()->getX(), m_game->getBonus()->getY());
		addItem(m_bonusItem);
	}
}
