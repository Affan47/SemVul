setProp(const QString & prop, const QString & value) {
	if (prop.compare("banded", Qt::CaseInsensitive) == 0) {
		setBanded(value == "Yes");
		return;
	}

	ItemBase::setProp(prop, value);
}
