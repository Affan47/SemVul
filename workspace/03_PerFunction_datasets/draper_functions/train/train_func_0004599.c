on(const char* short_name, const char* long_name,
			bool* optional, acceptable ac)
	{
		entry e;
		e.ac = ac;
		e.shared_required = s_parser->alloc<bool>(ac.required);
		e.optional = optional;
		if(e.optional) { *e.optional = false; }
		if(short_name) {
			m_map[std::string(short_name)] = e;
		}
		if(long_name) {
			m_map[std::string(long_name)] = e;
		}
	}
