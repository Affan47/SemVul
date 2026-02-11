wasClean(String &url, const int fg)
{
	if (reloadconfig)
		return false;
	UDSocket ipcsock;
	if (ipcsock.getFD() < 0) {
		syslog(LOG_ERR, "Error creating ipc socket to url cache");
		return false;
	}
	if (ipcsock.connect(o.urlipc_filename.c_str()) < 0) {
		syslog(LOG_ERR, "Error connecting via ipc to url cache: %s", strerror(errno));
		ipcsock.close();
		return false;
	}
	std::string myurl(" ");
	myurl += url.after("://").toCharArray();
	myurl[0] = fg+1;
	myurl += "\n";
#ifdef DGDEBUG
	std::cout << "sending cache search request: " << myurl;
#endif
	try {
		ipcsock.writeString(myurl.c_str());
	}
	catch(std::exception & e) {
#ifdef DGDEBUG
		std::cerr << "Exception writing to url cache" << std::endl;
		std::cerr << e.what() << std::endl;
#endif
		syslog(LOG_ERR, "Exception writing to url cache");
		syslog(LOG_ERR, "%s", e.what());
	}
	char reply;
	try {
		ipcsock.readFromSocket(&reply, 1, 0, 6);
	}
	catch(std::exception & e) {
#ifdef DGDEBUG
		std::cerr << "Exception reading from url cache" << std::endl;
		std::cerr << e.what() << std::endl;
#endif
		syslog(LOG_ERR, "Exception reading from url cache");
		syslog(LOG_ERR, "%s", e.what());
	}
	ipcsock.close();
	return reply == 'Y';
}
