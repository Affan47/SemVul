flipSvg(const QString & svg)
{
	QString newSvg = svg;

	newSvg.replace("\"" + ViewLayer::viewLayerXmlNameFromID(ViewLayer::Silkscreen1) + "\"", "\"" + ViewLayer::viewLayerXmlNameFromID(ViewLayer::Silkscreen0) + "\"");
	newSvg.replace("'" + ViewLayer::viewLayerXmlNameFromID(ViewLayer::Silkscreen1) + "'", "'" + ViewLayer::viewLayerXmlNameFromID(ViewLayer::Silkscreen0) + "'");
	newSvg.replace(ViewLayer::Silkscreen1Color, ViewLayer::Silkscreen0Color, Qt::CaseInsensitive);
    return flipSvgAux(newSvg);
}
