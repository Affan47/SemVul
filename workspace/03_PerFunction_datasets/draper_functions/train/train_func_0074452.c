Load()
{

	Clear();


	std::ifstream in(m_filename.c_str(), std::ios::in | std::ios::binary);
	if( !in )
		return;

	std::string line;

	while( std::getline(in, line) ) {
		std::string keyword;
		std::istringstream iss(line);
		iss >> keyword;

		if( keyword == "last_device" ) {
			iss >> std::ws;
			m_lastDevice.Clear();
			iss >> m_lastDevice;
		}
		else if( keyword == "verbose_logging" ) {
			int flag = 0;
			iss >> flag;
			m_verboseLogging = flag != 0;
		}
		else {

			if( keyword.substr(0, 2) == "X-" ) {
				iss >> std::ws;
				line.clear();
				std::getline(iss, line);
				m_keymap[keyword] = line;
			}
		}
	}

	m_loaded = true;
}
