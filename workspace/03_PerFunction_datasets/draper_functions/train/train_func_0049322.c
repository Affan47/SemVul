loadFromFile(const QString & fileName, ModelBase * referenceModel, bool checkViews) {
	QList<ModelPart *> modelParts;
	bool result = ModelBase::loadFromFile(fileName, referenceModel, modelParts, checkViews);
	if (result) {
		m_loadedFromFile = true;
		m_loadedFrom = fileName;
	}
	return result;
}
