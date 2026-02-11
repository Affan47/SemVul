prepareProps(ModelPart * modelPart, bool wantDebug, QStringList & keys)
{
    m_propsMap.clear();


	QHash<QString, QString> props = modelPart->properties();
	QString family = props.value("family", "").toLower();


	keys = props.keys();
	keys.removeOne("family");
	keys.push_front("family");


	QString partNumber = props.value(ModelPartShared::PartNumberPropertyName, "").toLower();
	keys.removeOne(ModelPartShared::PartNumberPropertyName);

	if (wantDebug) {
		props.insert("id", QString("%1 %2 %3")
			.arg(QString::number(id()))
			.arg(modelPart->moduleID())
			.arg(ViewLayer::viewLayerNameFromID(viewLayerID()))
		);
		keys.insert(1, "id");

		int insertAt = 2;
		PaletteItemBase * paletteItemBase = qobject_cast<PaletteItemBase *>(this);
		if (paletteItemBase != NULL) {
			props.insert("svg", paletteItemBase->filename());
			keys.insert(insertAt++, "svg");
		}
		props.insert("class", this->metaObject()->className());
		keys.insert(insertAt++, "class");

        if (modelPart->modelPartShared()) {
			props.insert("fzp",  modelPart->path());
			keys.insert(insertAt++, "fzp");
		}
	}


	if (hasPartNumberProperty()) {
		keys.append(ModelPartShared::PartNumberPropertyName);
	}

    return props;
}
