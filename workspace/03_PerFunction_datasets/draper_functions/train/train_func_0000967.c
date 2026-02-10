set(const QList<MUCItem>& items, MUCManager::Action action = MUCManager::Unknown) {
		action_ = action;
		iq_ = createIQ(doc(), "set", room_.full(), id());

		QDomElement muc = doc()->createElement("query");
		muc.setAttribute("xmlns", "http://jabber.org/protocol/muc#admin");
		iq_.appendChild(muc);

		foreach(MUCItem item, items) {
			muc.appendChild(item.toXml(*doc()));
		}
	}
