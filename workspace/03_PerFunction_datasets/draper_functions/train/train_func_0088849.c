Descent(Font &font_) {
	if (!(font_.GetID()))
		return 1;
	if (PFont(font_)->pfd) {
		PangoFontMetrics *metrics = pango_context_get_metrics(pcontext,
			PFont(font_)->pfd, pango_context_get_language(pcontext));
		int descent = doubleFromPangoUnits(pango_font_metrics_get_descent(metrics));
		pango_font_metrics_unref(metrics);
		return descent;
	}
	return 0;
}
