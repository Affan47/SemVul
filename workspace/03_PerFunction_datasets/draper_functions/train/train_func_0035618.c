compareTo(const Object *data_b) const
	{
		info_pos *b = (info_pos*)data_b;
		uint da = line;
		uint db = b->line;
		if (da == db) {
			return ofs - b->ofs;
		}
		return da - db;
	}
