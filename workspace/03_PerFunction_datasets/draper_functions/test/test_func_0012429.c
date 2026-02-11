addMessage(callback &callback) const
{
	if (isDestroyed(callback))
		return NULL;

	return new mail::nntp::add(myserver, &callback);
}
