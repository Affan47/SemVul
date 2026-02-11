addSticky(ItemBase * stickyBase, bool stickem) {
	stickyBase = stickyBase->layerKinChief();


	if (stickem) {
		if (!isBaseSticky()) {
			foreach (ItemBase * oldstickingTo, m_stickyList.values()) {
				if (oldstickingTo == stickyBase) continue;

				oldstickingTo->addSticky(this, false);
			}
			m_stickyList.clear();
		}
		m_stickyList.insert(stickyBase->id(), stickyBase);
	}
	else {
		m_stickyList.remove(stickyBase->id());
	}
}
