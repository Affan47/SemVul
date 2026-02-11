binding_success()
	{
		refAddr = stunBinding->reflexiveAddress();
		refPort = stunBinding->reflexivePort();

		delete stunBinding;
		stunBinding = 0;

		emit q->addressesChanged();
	}
