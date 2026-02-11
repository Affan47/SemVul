toString() const
	{
		const UInt8* bytes = reinterpret_cast<const UInt8*>(&_addr);
		std::string result;
		result.reserve(16);
		NumberFormatter::append(result, bytes[0]);
		result.append(".");
		NumberFormatter::append(result, bytes[1]);
		result.append(".");
		NumberFormatter::append(result, bytes[2]);
		result.append(".");
		NumberFormatter::append(result, bytes[3]);
		return result;
	}
