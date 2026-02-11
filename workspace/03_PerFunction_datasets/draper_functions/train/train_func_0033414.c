enableWidgets()
{
	int const selection = spacingCO->currentIndex();
	bool const custom = (selection == spacingCO->count() - 1);
	valueLE->setEnabled(custom);
	unitCO->setEnabled(custom);
	if (math_mode_) {
		fillPatternCO->setEnabled(false);
		keepCB->setEnabled(false);
		return;
	}
	fillPatternCO->setEnabled(selection == 6);
	bool const no_pattern = fillPatternCO->currentIndex() == 0;
	bool const enable_keep =
		selection == 0 || selection == 3  ||
		(selection == 6 && no_pattern) || custom;
	keepCB->setEnabled(enable_keep);
}
