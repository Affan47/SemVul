do_local(int id, const QByteArray &name)
	{
		Item *i = getItemById(id);
		Q_ASSERT(i);


		if(i->longLived)
			releaseItem(i);
		emit resolve_useLocal(id, name);
	}
