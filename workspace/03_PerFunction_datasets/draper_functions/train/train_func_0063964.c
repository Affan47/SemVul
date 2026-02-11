drop_priv_completely()
{


	int rc = seteuid(o.root_user);
	if (rc == -1) {
		syslog(LOG_ERR, "%s", "Unable to seteuid(suid)");
#ifdef DGDEBUG
		std::cout << strerror(errno) << std::endl;
#endif
		return false;
	}
	rc = setuid(o.proxy_user);
	if (rc == -1) {
		syslog(LOG_ERR, "%s", "Unable to setuid()");
		return false;
	}
	return true;
}
