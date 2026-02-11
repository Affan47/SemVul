setParentLayer(ViewLayer * parent) {
	m_parentLayer = parent;
	if (parent) {
		parent->m_childLayers.append(this);
	}
}
