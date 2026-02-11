makeSvg(bool blackOnly, double dpi, double printerScale, bool includeTransform) {
	double w, h;
	QString svg = makeSvgAux(blackOnly, dpi, printerScale, w, h);
	if (includeTransform) {
		QTransform t = transform();
		if (!t.isIdentity()) {
			svg = TextUtils::svgTransform(svg, t, false, QString());
		}
	}
	return svg;
}
