erasePollFD(vector<struct pollfd>::iterator &itt)
{

    boost::mutex::scoped_lock lock(_poll_mutex);
    if (_pollfds.size() == 1) {
 	_pollfds.clear();
     } else {
	_pollfds.erase(itt);
    }
}
