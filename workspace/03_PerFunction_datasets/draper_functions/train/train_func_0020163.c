available() const {
    PROFILE("Backend::available");

    if (config.debug()) {
	ostringstream o;
	o << "Back end " << description() << ": "
	  << livestr() << ", " << upstr() << ", "
	  << connections() << " connections, "
	  << IPStore::anticipated(balancerindex()) << " anticipated, "
	  << maxconn() << " max\n";
	_debugmsg(o.str());
    }
    if (!maxconn())
	return (islive && isup);
    return (islive &&
	    isup &&
	    (connections() + IPStore::anticipated(balancerindex()) <
	     maxconn()));
}
