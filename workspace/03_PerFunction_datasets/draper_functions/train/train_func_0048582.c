parse_date_mask(const char * date_str, struct std::tm * result)
  {
    if (! date_t::input_format.empty()) {
      std::memset(result, -1, sizeof(struct std::tm));
      if (strptime(date_str, date_t::input_format.c_str(), result))
	return true;
    }
    for (const char ** f = date_t::formats; *f; f++) {
      std::memset(result, -1, sizeof(struct std::tm));
      if (strptime(date_str, *f, result))
	return true;
    }
    return false;
  }
