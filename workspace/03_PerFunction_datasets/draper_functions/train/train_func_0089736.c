toggleMark(size_t n)
{
	if (n >= size())
		return;

	size_t sIndex=getServerIndex(n);

	myServer *s=getServer();

	if (s && s->server)
	{
		mail::messageInfo msgInfo=
			s->server->getFolderIndexInfo(sIndex);

		msgInfo.marked= !msgInfo.marked;

		statusBar->clearstatus();
		statusBar->status(msgInfo.marked
				  ? _("Marking message...")
				  : _("Unmarking message..."));

		DelUndelCallback *cb= new DelUndelCallback;

		if (!cb)
			outofmemory();

		try {
			s->server->saveFolderIndexInfo(sIndex, msgInfo, *cb);
		} catch (...) {
			delete cb;
			LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
		}
	}
}
