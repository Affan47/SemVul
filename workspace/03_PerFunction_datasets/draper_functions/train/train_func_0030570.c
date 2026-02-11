checkDbAge()
{
    struct stat s;

    if (lstat(Config::stamp().c_str(), &s) < 0)
      	Config::touchStamp();
	else if (time(0) - s.st_mtime > Config::maxDbAge() * 24 * 3600) {
		cout.flush();
		cerr << "*** Warning: The database is older than "
		 	<< Config::maxDbAge() << " days.\n*** Run 'paco -ua' to update it.\n";
	}
}
