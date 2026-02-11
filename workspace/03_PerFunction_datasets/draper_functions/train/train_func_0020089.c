fetch_handler(const Element* e, const String& name)
{
    if (const Handler* h = handler(e, name))
	return *h;
    else
	return Handler(name);
}
