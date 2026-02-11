collectExtraInfo(QWidget * parent, const QString & family, const QString & prop, const QString & value, bool swappingEnabled, QString & returnProp, QString & returnValue, QWidget * & returnWidget, bool & hide)
{
	if (prop.compare("chip label", Qt::CaseInsensitive) == 0) {
		returnProp = tr("label");
		returnValue = m_chipLabel;

		QLineEdit * e1 = new QLineEdit(parent);
		e1->setEnabled(swappingEnabled);
		e1->setText(m_chipLabel);
		connect(e1, SIGNAL(editingFinished()), this, SLOT(chipLabelEntry()));
		e1->setObjectName("infoViewLineEdit");


		returnWidget = e1;

		return true;
	}

    if (prop.compare("hole size", Qt::CaseInsensitive) == 0) {
        return collectHoleSizeInfo(TheHoleThing.holeSizeValue, parent, swappingEnabled, returnProp, returnValue, returnWidget);
	}

	return PaletteItem::collectExtraInfo(parent, family, prop, value, swappingEnabled, returnProp, returnValue, returnWidget, hide);
}
