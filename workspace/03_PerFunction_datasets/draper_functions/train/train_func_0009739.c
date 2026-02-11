get_float(const char * const key) const
{
	const char * const obj = (const char * const)(this->lookup(key));
	if (obj == NULL)
		 throw new ValueNotSpecifiedException(key);
	return atof(obj);
}
