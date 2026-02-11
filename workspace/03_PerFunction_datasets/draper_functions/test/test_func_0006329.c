retrieveSvg(ViewLayer::ViewLayerID viewLayerID, QHash<QString, QString> & svgHash, bool blackOnly, double dpi, double & factor)
{
	switch (viewLayerID) {
		case ViewLayer::Breadboard:
		case ViewLayer::Icon:
			break;
		default:
			return Capacitor::retrieveSvg(viewLayerID, svgHash, blackOnly, dpi, factor);
	}

	QString svg = getColorSVG(prop("color"), viewLayerID);
	if (svg.isEmpty()) return "";

    return PaletteItemBase::normalizeSvg(svg, viewLayerID, blackOnly, dpi, factor);
}
