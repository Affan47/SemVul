loadFromModel(PaletteModel * model) {
	ModelPart* root = model->root();
	QList<QObject *>::const_iterator i;
    for (i = root->children().constBegin(); i != root->children().constEnd(); ++i) {
		ModelPart* mp = qobject_cast<ModelPart *>(*i);
		if (mp == NULL) continue;

		QDomElement instance = mp->instanceDomElement();
		if (instance.isNull()) continue;

		QDomElement views = instance.firstChildElement("views");
		if (views.isNull()) continue;

		QString name = ViewLayer::viewIDXmlName(ViewLayer::IconView);
		QDomElement view = views.firstChildElement(name);
		if (view.isNull()) continue;

		QDomElement geometry = view.firstChildElement("geometry");
		if (geometry.isNull()) continue;

		setItemAux(mp);
	}
}
