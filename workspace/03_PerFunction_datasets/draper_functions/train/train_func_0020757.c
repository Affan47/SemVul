normalize_fqan(std::string fqan) {

	std::string nfqan = Arc::trim(fqan," \"");

	std::size_t pos = nfqan.find("VO=");
      	if(pos != std::string::npos) nfqan.erase(pos, 3);
	pos = nfqan.find("Group=");
      	if(pos != std::string::npos) nfqan.erase(pos, 6);

	pos = nfqan.find("/Role=NULL");
	if(pos != std::string::npos) nfqan.erase(pos, 10);
	pos = nfqan.find("/Capability=NULL");
	if(pos != std::string::npos) nfqan.erase(pos, 16);

	return nfqan;
}
