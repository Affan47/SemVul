parse_ifexpr(std::ostream* os)
{
	Object params;
	if (getparamlist(params))
		return false;
	Object::ArrayType& pl = params.array();

	if (pl.empty())
	{
		recorderror("Syntax error, expected expression");
		return false;
	}
	else if (pl.size() > 1)
		recorderror("Warning: extra parameters ignored");

	Object& obj = *pl[0].get();

	if (obj.gettype() != Object::type_scalar)
	{
		recorderror("Error: Excpected scalar expression");
		return false;
	}

	int64_t lwork;
	lwork = str2num(obj.scalar().c_str());

	if (lwork)
		parse_block(os);
	else
		ignore_block();

	return !!lwork;
}
