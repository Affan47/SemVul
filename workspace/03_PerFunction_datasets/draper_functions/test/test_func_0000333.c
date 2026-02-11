do_local_ready(int id, const QList<XMPP::NameRecord> &results)
	{
		Item *i = getItemById(id);
		Q_ASSERT(i);

		if(!i->longLived)
		{

			if(i->req)
				i->req->cancel();


			releaseItem(i);
		}

		emit resolve_resultsReady(id, results);
	}
