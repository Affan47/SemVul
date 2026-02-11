parse_size()
{
	Object params;
	Token<> result;
	result.type = token_integer;
	if (getparamlist(params))
		return result;
	Object::ArrayType& pl = params.array();
	size_t size=0;

	Object::ArrayType::const_iterator it(pl.begin()), end(pl.end());
	for (; it != end; ++it)
	{
		Object& obj = *(*it).get();
		if (obj.gettype() == Object::type_array)
			size+= obj.array().size();
		else if (obj.gettype() == Object::type_hash)
			size+= obj.hash().size() * 2;
		else if (obj.gettype() == Object::type_scalar)
			size+= !obj.scalar().empty();
	}
	num2str(size, result.value);

	return result;
}
