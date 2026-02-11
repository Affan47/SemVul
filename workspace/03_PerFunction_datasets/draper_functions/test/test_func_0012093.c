jr_finished()
	{
		JDnsServiceResolve *jr = (JDnsServiceResolve *)sender();
		ResolveItem *i = resolveItemList.itemByResolve(jr);
		Q_ASSERT(i);


		QMap<QString,QByteArray> attribs;
		for(int n = 0; n < jr->attribs.count(); ++n)
		{
			const QByteArray &a = jr->attribs[n];
			QString key;
			QByteArray value;
			int x = a.indexOf('=');
			if(x != -1)
			{
				key = QString::fromLatin1(a.mid(0, x));
				value = a.mid(x + 1);
			}
			else
			{
				key = QString::fromLatin1(a);
			}

			attribs.insert(key, value);
		}


		Q_ASSERT(jr->have4 || jr->have6);

		QList<ResolveResult> results;
		if(jr->have6)
		{
			ResolveResult r;
			r.attributes = attribs;
			r.address = jr->addr6;
			r.port = jr->port;
			r.hostName = jr->host;
			results += r;
		}
		if(jr->have4)
		{
			ResolveResult r;
			r.attributes = attribs;
			r.address = jr->addr4;
			r.port = jr->port;
			r.hostName = jr->host;
			results += r;
		}

		int id = i->id;
		resolveItemList.remove(i);
		emit resolve_resultsReady(id, results);
	}
