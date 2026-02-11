interpretCF(QPDFObjectHandle cf)
{
    if (cf.isName())
    {
	std::string filter = cf.getName();
	if (this->crypt_filters.count(filter) != 0)
	{
	    return this->crypt_filters[filter];
	}
	else if (filter == "/Identity")
	{
	    return e_none;
	}
	else
	{
	    return e_unknown;
	}
    }
    else
    {

	return e_none;
    }
}
