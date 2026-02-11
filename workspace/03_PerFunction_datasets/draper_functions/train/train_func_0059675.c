readFile(const char *filename, unsigned int* whichlist, bool sortsw, bool cache, const char *listname)
{
	int res = o.lm.newItemList(filename, sortsw, 1, true);
	if (res < 0) {
		if (!is_daemonised) {
			std::cerr << "Error opening " << listname << std::endl;
		}
		syslog(LOG_ERR, "Error opening %s", listname);
		return false;
	}
	(*whichlist) = (unsigned) res;
	if (!(*o.lm.l[(*whichlist)]).used) {
		if (sortsw)
			(*o.lm.l[(*whichlist)]).doSort(true);
		else
			(*o.lm.l[(*whichlist)]).doSort(false);
		if (cache && createlistcachefiles) {
			if (!(*o.lm.l[(*whichlist)]).createCacheFile()) {
				return false;
			}
		}
		(*o.lm.l[(*whichlist)]).used = true;
	}
	return true;
}
