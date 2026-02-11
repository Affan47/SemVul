hasCustomSVG() {
	switch (m_viewID) {
		case ViewLayer::PCBView:
		case ViewLayer::SchematicView:
		case ViewLayer::BreadboardView:
			return true;
		default:
			return ItemBase::hasCustomSVG();
	}
}
