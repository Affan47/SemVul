getColor(KicadModule2Svg::PadLayer padLayer) {
	switch (padLayer) {
		case ToCopper0:
			return ViewLayer::Copper0Color;
			break;
		case ToCopper1:
			return ViewLayer::Copper1Color;
			break;
		default:
			DebugDialog::debug("kicad getcolor with unknown layer");
			return "#FF0000";
	}
}
