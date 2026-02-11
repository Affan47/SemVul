Save(std::string file, enum plist_format format) const
{
	switch(format) {
		case PL_FORMAT_M3U:
			if(file.length() < 4 ||
			   strcasecmp(file.substr(file.length() - 4).c_str(), ".m3u")) {
				file += ".m3u";
			}


			std::ofstream out_list(file.c_str());
			if(!out_list) return E_PL_BAD;


			std::vector<PlayItem>::const_iterator p = queue.begin();
			while(p != queue.end()) {
				out_list << (*p).filename << std::endl;
				p++;
			}
	}
	return E_PL_SUCCESS;
}
