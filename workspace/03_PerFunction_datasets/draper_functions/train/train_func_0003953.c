production(bool checked) {
	Q_UNUSED(checked);

	QString units;
	if (sender() == m_homebrewButton) {
		enableCustom(false);
		changeHoleSize(sender()->property("holesize").toString() + "," + sender()->property("ringthickness").toString());
		setTraceWidth(16);
        setDefaultKeepout();
	}
	else if (sender() == m_professionalButton) {
		enableCustom(false);
		changeHoleSize(sender()->property("holesize").toString() + "," + sender()->property("ringthickness").toString());
		setTraceWidth(24);
        setDefaultKeepout();
	}
	else if (sender() == m_customButton) {
		enableCustom(true);
	}
}
