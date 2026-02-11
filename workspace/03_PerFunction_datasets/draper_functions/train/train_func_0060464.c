Serialize(const LJArray& array, LJString& result)
{
	result += "[";

	for(LJArray::const_iterator entry = array.begin(); entry != array.end(); ++entry)
	{
		if(entry != array.begin())
			result += ",";

		Serialize(*entry, result);
	}

	result += "]";
}
