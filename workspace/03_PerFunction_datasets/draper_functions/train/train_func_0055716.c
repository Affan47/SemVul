vsprintf(std::ostringstream& outstr, const char* format, va_list ap) {
	char* chr = const_cast<char*>(format);

	if (!chr) {
		return;
	}

	while (*chr) {

		if (*chr != '%' || *++chr == '%') {
			outstr << *chr++;
			continue;
		}

		switch (*chr) {

			case 'i':
				outstr << va_arg(ap, int);
				break;

			case 'd':
				outstr << va_arg(ap, double);
				break;

			case 'N':
				outstr << va_arg(ap, size_t);
				break;

			case 'l':
				outstr << va_arg(ap, int64_t);
				break;
			case 'T': {
					const Type* type = va_arg(ap, const Type*);

					if (type) {
						outstr << type->getName();
					} else {
						outstr << "null";
					}
				}
				break;

			case 'S':
				outstr << *va_arg(ap, const CString*);
				break;

			case 's':
				outstr << va_arg(ap, const char*);
				break;

			case 'v':
				va_arg(ap, Value*)->dump(outstr);
				break;

			case '@':
				outstr << std::hex << va_arg(ap, void*);
				break;
		}
		++chr;
	}
}
