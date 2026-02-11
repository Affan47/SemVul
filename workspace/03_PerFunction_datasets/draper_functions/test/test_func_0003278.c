async_removeEntry(const QString &entryId)
	{
		KeyStoreOperation *op = new KeyStoreOperation(this);

		connect(op, SIGNAL(finished()), SLOT(op_finished()), Qt::QueuedConnection);
		op->type = KeyStoreOperation::RemoveEntry;
		op->trackerId = trackerId;
		op->entryId = entryId;
		ops += op;
		op->start();
	}
