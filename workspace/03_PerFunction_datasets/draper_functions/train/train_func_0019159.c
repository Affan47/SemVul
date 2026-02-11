isRemoteUrl(std::string url)
{
	mail::driver **l=mail::driver::get_driver_list();

	while (*l)
	{
		bool flag;

		if ( (*(*l)->isRemote_func)(url, flag))
			return flag;

		l++;
	}

	return false;
}
