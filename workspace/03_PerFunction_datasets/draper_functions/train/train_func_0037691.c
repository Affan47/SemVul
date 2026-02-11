exportSvg(double res, bool selectedItems, bool flatten, const QString & fileName)
{
	FileProgressDialog * fileProgressDialog = exportProgress();
	LayerList viewLayerIDs;
	foreach (ViewLayer * viewLayer, m_currentGraphicsView->viewLayers()) {
		if (viewLayer == NULL) continue;
		if (!viewLayer->visible()) continue;

		viewLayerIDs << viewLayer->viewLayerID();
	}

	RenderThing renderThing;
    renderThing.printerScale = GraphicsUtils::SVGDPI;
    renderThing.blackOnly = false;
    renderThing.dpi = res;
    renderThing.selectedItems = selectedItems;
    renderThing.hideTerminalPoints = true;
    renderThing.renderBlocker = false;
	QString svg = m_currentGraphicsView->renderToSVG(renderThing, NULL, viewLayerIDs);
	if (svg.isEmpty()) {

		return;
	}

	if (selectedItems == false && flatten == false) {
		exportSvgWatermark(svg, res);
	}

    TextUtils::writeUtf8(fileName, TextUtils::convertExtendedChars(svg));
	delete fileProgressDialog;
}
