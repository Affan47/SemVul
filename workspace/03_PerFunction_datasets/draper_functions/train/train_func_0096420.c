res_ftime(std::string& file, int diff = 0) {
	struct stat statbuf = {0};
	stat(file.c_str(), &statbuf);
	time_t tt = statbuf.st_mtime + diff;
	struct tm* p=gmtime(&tt);


	char buf[256];


	sprintf(buf, "%s, %02d %s %04d %02d:%02d:%02d GMT",
		wdays[p->tm_wday],
		p->tm_mday,
		months[p->tm_mon],
		p->tm_year+1900,
		p->tm_hour,
		p->tm_min,
		p->tm_sec);
	return buf;
}
