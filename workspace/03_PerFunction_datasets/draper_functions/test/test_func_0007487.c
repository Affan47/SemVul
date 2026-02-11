fromXml(const QDomElement& e)
{
	if (e.tagName() != "item")
		return;

	jid_ = Jid(e.attribute("jid"));
	nick_ = e.attribute("nick");


	if (e.attribute("affiliation") == "owner") {
		affiliation_ = Owner;
	}
	else if (e.attribute("affiliation") == "admin") {
		affiliation_ = Admin;
	}
	else if (e.attribute("affiliation") == "member") {
		affiliation_ = Member;
	}
	else if (e.attribute("affiliation") == "outcast") {
		affiliation_ = Outcast;
	}
	else if (e.attribute("affiliation") == "none") {
		affiliation_ = NoAffiliation;
	}


	if (e.attribute("role") == "moderator") {
		role_ = Moderator;
	}
	else if (e.attribute("role") == "participant") {
		role_ = Participant;
	}
	else if (e.attribute("role") == "visitor") {
		role_ = Visitor;
	}
	else if (e.attribute("role") == "none") {
		role_ = NoRole;
	}

	for(QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
		QDomElement i = n.toElement();
		if(i.isNull())
			continue;

		if (i.tagName() == "actor")
			actor_ = Jid(i.attribute("jid"));
		else if (i.tagName() == "reason")
			reason_ = i.text();
	}
}
