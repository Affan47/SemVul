addPointArgument(const std::string& name, GLEPointDataObject* defaultValue, bool mandatory) {
	unsigned int result = addArgument(name, GLEObjectTypePoint, mandatory);
	if (defaultValue != 0) {
		m_Defaults->setObject(result, defaultValue);
	}
	return result;
}
