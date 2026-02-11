simplePropertyEntry(const QString & text) {

	FocusOutComboBox * focusOutComboBox = qobject_cast<FocusOutComboBox *>(sender());
	if (focusOutComboBox == NULL) return;

	foreach (PropertyDef * propertyDef, m_comboBoxes.keys()) {
		if (m_comboBoxes.value(propertyDef) == focusOutComboBox) {
			InfoGraphicsView * infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
			if (infoGraphicsView != NULL) {
				infoGraphicsView->setProp(this, propertyDef->name, "", m_propertyDefs.value(propertyDef, ""), text, true);
			}
			break;
		}
	}
}
