getParamString() const {
	return QString("%1 %2")
		.arg(m_sketchWidget->viewName())
		.arg((m_crossViewType == BaseCommand::SingleView) ? "single-view" : "cross-view");
}
