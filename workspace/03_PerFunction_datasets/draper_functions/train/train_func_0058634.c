fail(string message)
{
	originalCallback.fail(message);
	delete this;
}
