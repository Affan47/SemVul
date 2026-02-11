rotateItem(double degrees, bool includeRatsnest) {
	PaletteItemBase::rotateItem(degrees, includeRatsnest);
	for (int i = 0; i < m_layerKin.count(); i++) {
		m_layerKin[i]->rotateItem(degrees, includeRatsnest);
	}
}
