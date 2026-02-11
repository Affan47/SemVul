tryPublish()
	{
		QString me = QHostInfo::localHostName();
		if(counter > 1)
			me += QString("-%1").arg(counter);

		host = escapeDomainPart(me.toUtf8()) + ".local.";

		if(use6)
			tryPublish6();
		if(use4)
			tryPublish4();
	}
