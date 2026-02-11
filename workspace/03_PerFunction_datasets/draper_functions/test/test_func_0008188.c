on_pagebreakCB_stateChanged()
{
	bool pbreak = (pagebreakCB->checkState() == Qt::Checked);
	innerBoxCO->setEnabled(!pbreak);
	widthED->setEnabled(!pbreak);
	widthUnitsLC->setEnabled(!pbreak);
	if (!pbreak) {
		on_typeCO_activated(typeCO->currentIndex());
		return;
	}
	valignCO->setEnabled(false);
	ialignCO->setEnabled(false);
	halignCO->setEnabled(false);
	heightCB->setEnabled(false);
	heightED->setEnabled(false);
	heightUnitsLC->setEnabled(false);
	setSpecial(false);
	changed();
}
