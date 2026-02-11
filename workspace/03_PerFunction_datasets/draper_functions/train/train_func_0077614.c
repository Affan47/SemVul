fromXml(const QDomElement &e)
{
	sid = e.attribute("sid"),
	seq = e.attribute("seq").toInt(),
	data = QCA::Base64().stringToArray(e.text()).toByteArray();
	return *this;
}
