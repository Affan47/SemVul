as_utf8_impl(const wchar_t* str, size_t length)
	{

		size_t size = as_utf8_begin(str, length);


		std::string result;
		result.resize(size);


		if (size > 0) as_utf8_end(&result[0], size, str, length);

		return result;
	}
