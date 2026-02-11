SetBackground(const std::string& filename, PG_Draw::BkMode mode) {
	if (filename.empty()) {
		return false;
	}

	if ( !SetBackground ( LoadSurface(filename), mode, true ))
		PG_LogWRN("Failed to load '%s'",(char*)filename.c_str());

	return false;
}
