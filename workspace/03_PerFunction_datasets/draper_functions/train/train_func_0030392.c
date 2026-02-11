CallNewHandler()
{
	new_handler newHandler = set_new_handler(NULL);
	if (newHandler)
		set_new_handler(newHandler);

	if (newHandler)
		newHandler();
	else
		throw std::bad_alloc();
}
