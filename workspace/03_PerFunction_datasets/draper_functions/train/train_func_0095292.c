messageTextCallback(size_t n,
							     string text)
{
	if (store)
		store->store(n, text);
}
