convertFromXmlName(const QString & xmlName) {
    QString result = ItemBase::TranslatedPropertyNames.value(XmlNamesToNames.value(xmlName));
    if (result.isEmpty()) return xmlName;
    return result;
}
