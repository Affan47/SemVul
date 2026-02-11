isBypassURL(String * url, const char *magic, const char *clientip, bool *isvirusbypass)
{
	if ((*url).length() <= 45)
		return false;


	bool filterbypass = false;
	bool virusbypass = false;
	if ((isvirusbypass == NULL) && ((*url).contains("GBYPASS="))) {
		filterbypass = true;
	} else if ((isvirusbypass != NULL) && (*url).contains("GIBYPASS=")) {
		virusbypass = true;
	}
	if (!(filterbypass || virusbypass))
		return 0;

#ifdef DGDEBUG
	std::cout << "URL " << (filterbypass ? "GBYPASS" : "GIBYPASS") << " found checking..." << std::endl;
#endif

	String url_left((*url).before(filterbypass ? "GBYPASS=" : "GIBYPASS="));
	url_left.chop();
	String url_right((*url).after(filterbypass ? "GBYPASS=" : "GIBYPASS="));

	String url_hash(url_right.subString(0, 32));
	String url_time(url_right.after(url_hash.toCharArray()));
#ifdef DGDEBUG
	std::cout << "URL: " << url_left << ", HASH: " << url_hash << ", TIME: " << url_time << std::endl;
#endif

	String mymagic(magic);
	mymagic += clientip;
	mymagic += url_time;
	String hashed(url_left.md5(mymagic.toCharArray()));

	if (hashed != url_hash) {
#ifdef DGDEBUG
		std::cout << "URL " << (filterbypass ? "GBYPASS" : "GIBYPASS") << " hash mismatch" << std::endl;
#endif
		return 0;
	}

	time_t timen = time(NULL);
	time_t timeu = url_time.toLong();

	if (timeu < 1) {
#ifdef DGDEBUG
		std::cout << "URL " << (filterbypass ? "GBYPASS" : "GIBYPASS") << " bad time value" << std::endl;
#endif
		return 1;
	}
	if (timeu < timen) {
#ifdef DGDEBUG
		std::cout << "URL " << (filterbypass ? "GBYPASS" : "GIBYPASS") << " expired" << std::endl;
#endif
		return 1;
	}
#ifdef DGDEBUG
	std::cout << "URL " << (filterbypass ? "GBYPASS" : "GIBYPASS") << " not expired" << std::endl;
#endif
	if (virusbypass)
		(*isvirusbypass) = true;
	return (int) timeu;
}
