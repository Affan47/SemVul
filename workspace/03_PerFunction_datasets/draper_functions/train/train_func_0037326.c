func_avg(std::ostream& os, TPT::Object& params)
{
	Object::ArrayType& pl = params.array();
	std::string result;
	int64_t lwork = 0, count = 0;
	bool iserr = true;

	Object::ArrayType::const_iterator it(pl.begin()), end(pl.end());
	for (; it != end; ++it)
	{
		Object& obj = *(*it).get();
		if (obj.gettype() == Object::type_array)
		{
			Object::ArrayType& temp = obj.array();
			Object::ArrayType::const_iterator ait(temp.begin()), aend(temp.end());
			for (; ait != aend; ++ait)
			{
				Object& subobj = *(*it).get();
				if (subobj.gettype() == Object::type_scalar)
				{
					lwork+= str2num(subobj.scalar().c_str());
					++count;
				}
			}
		}
		else if (obj.gettype() == Object::type_scalar)
		{
			lwork+= str2num(obj.scalar().c_str());
			++count;
		}
		else
			iserr = true;
	}
	count = !count ? 1 : count;
	lwork/= count;
	num2str(lwork, result);
	os << result;

	return iserr;
}
