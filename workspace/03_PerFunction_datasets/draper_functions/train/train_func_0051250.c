eventToLine(PsiEvent *e)
{
	int subflags = 0;
	QString sTime, sType, sOrigin, sFlags;

	if(e->type() == PsiEvent::Message) {
		MessageEvent *me = (MessageEvent *)e;
		const Message &m = me->message();
		const UrlList urls = m.urlList();

		if(!m.subject().isEmpty())
			subflags |= 1;
		if(!urls.isEmpty())
			subflags |= 2;

		sTime = m.timeStamp().toString(Qt::ISODate);
		int n = 0;
		if(m.type() == "chat")
			n = 1;
		else if(m.type() == "error")
			n = 4;
		else if(m.type() == "headline")
			n = 5;
		sType.setNum(n);
		sOrigin = e->originLocal() ? "to": "from";
		sFlags = "N---";

		if(subflags != 0)
			sFlags[1] = QString::number(subflags,16)[0];


		QString line = "|" + sTime + "|" + sType + "|" + sOrigin + "|" + sFlags + "|";

		if(subflags & 1) {
			line += logencode(m.subject()) + "|";
		}
		if(subflags & 2) {
			const Url &url = urls.first();
			line += logencode(url.url()) + "|";
			line += logencode(url.desc()) + "|";
		}
		line += logencode(m.body());

		return line;
	}
	else if(e->type() == PsiEvent::Auth) {
		AuthEvent *ae = (AuthEvent *)e;
		sTime = ae->timeStamp().toString(Qt::ISODate);
		QString subType = ae->authType();
		int n = 0;
		if(subType == "subscribe")
			n = 3;
		else if(subType == "subscribed")
			n = 6;
		else if(subType == "unsubscribe")
			n = 7;
		else if(subType == "unsubscribed")
			n = 8;
		sType.setNum(n);
		sOrigin = e->originLocal() ? "to": "from";
		sFlags = "N---";


		QString line = "|" + sTime + "|" + sType + "|" + sOrigin + "|" + sFlags + "|";
		line += logencode(subType);

		return line;
	}

	return "";
}
