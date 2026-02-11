updateSizes(HoleSettings &  holeSettings) {
	if (holeSettings.sizesComboBox == NULL) return;

	int newIndex = -1;

	QPointF current(TextUtils::convertToInches(holeSettings.holeDiameter), TextUtils::convertToInches(holeSettings.ringThickness));
	for (int ix = 0; ix < holeSettings.sizesComboBox->count(); ix++) {
		QString key = holeSettings.sizesComboBox->itemText(ix);
		QString value = holeSettings.holeThing->holeSizes.value(key, "");
		QStringList sizes;
		if (value.isEmpty()) {
			sizes = key.split(",");
		}
		else {
			sizes = value.split(",");
		}
		if (sizes.count() < 2) continue;

		QPointF p(TextUtils::convertToInches(sizes.at(0)), TextUtils::convertToInches(sizes.at(1)));
		if (p == current) {
			newIndex = ix;
			break;
		}
	}

	if (newIndex < 0) {
		QString newItem = holeSettings.holeDiameter + "," + holeSettings.ringThickness;
		holeSettings.sizesComboBox->addItem(newItem);
		newIndex = holeSettings.sizesComboBox->findText(newItem);

		holeSettings.holeThing->holeSizes.insert(newItem, newItem);
        holeSettings.holeThing->holeSizeKeys.prepend(newItem);
	}


	bool wasBlocked = holeSettings.sizesComboBox->blockSignals(true);
	holeSettings.sizesComboBox->setCurrentIndex(newIndex);
	holeSettings.sizesComboBox->blockSignals(wasBlocked);
}
