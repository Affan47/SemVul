serialize(std::stringstream& ss, size_t indentLevel) const
	{
		ss << "[";
		for (size_t i = 1; i < data.size(); ++i)
		{
			data[i - 1]->serialize(ss, indentLevel);
			ss << ", ";
		}
		if (data.size() > 0)
		{
			data[size() - 1]->serialize(ss, indentLevel);
		}
		ss << "]";
	}
