EmitEvents(EventHandler& eventHandler) const
	{
		eventHandler.OnDocumentStart(m_mark);
		AliasManager am;
		EmitEvents(am, eventHandler);
		eventHandler.OnDocumentEnd();
	}
