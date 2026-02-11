add(const string& media, const string& selector, const string& property, const string& value)
{
	if(settings["preserve_css"]) {
		return;
	}

	if(css[media][selector].has(property))
	{
		if( !is_important(css[media][selector][property]) || (is_important(css[media][selector][property]) && is_important(value)) )
		{
			css[media][selector].erase(property);
			css[media][selector][property] = trim(value);
		}
	}
	else
	{
		css[media][selector][property] = trim(value);
	}
}
