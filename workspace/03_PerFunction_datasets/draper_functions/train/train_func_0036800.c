checkNewMail(mail::callback &callback)
{
	if (!ready(callback))
		return;

	if (currentFolder)
		currentFolder->resetMailCheckTimer();

	installForegroundTask(smap ?
			      (imapHandler *)new smapNoopExpunge("NOOP",
								 callback,
								 *this)
			      : new mail::imapCHECKMAIL(callback));
}
