get_finished(int, bool err)
{
	if (err) {
		emit error(http_->errorString());
	}
	else {

		QDomDocument doc;
		if (!doc.setContent(http_->readAll())) {
			emit error(tr("Unable to parse server list"));
			return;
		}


		QStringList servers;
		QDomNodeList items = doc.elementsByTagName("item");
		for (int i = 0; i < items.count(); i++) {
			QString jid = items.item(i).toElement().attribute("jid");
			if (!jid.isEmpty()) {
				servers.push_back(jid);
			}
		}
		emit listReceived(servers);
	}
}
