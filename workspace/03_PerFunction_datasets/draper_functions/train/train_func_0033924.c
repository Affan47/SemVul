ready(mail::callback &callback)
{
	if (socketConnected())
		return true;

	callback.fail("Account connection closed.");
	return false;
}
