silkLayers(ViewLayer::ViewLayerPlacement viewLayerPlacement) {
	static LayerList bottom;
	static LayerList top;
	if (bottom.isEmpty()) {
		bottom << ViewLayer::Silkscreen0 << ViewLayer::Silkscreen0Label;
	}
	if (top.isEmpty()) {
		top << ViewLayer::Silkscreen1 << ViewLayer::Silkscreen1Label;
	}
	if (viewLayerPlacement == ViewLayer::NewTop) return top;

	return bottom;
}
