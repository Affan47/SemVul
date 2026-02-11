enter_rfmon_mode(pcap_t *handle, int sock_fd, const char *device)
{
#if defined(HAVE_LIBNL) || defined(IW_MODE_MONITOR)
	int ret;
#endif

#ifdef HAVE_LIBNL
	ret = enter_rfmon_mode_mac80211(handle, sock_fd, device);
	if (ret < 0)
		return ret;
	if (ret == 1)
		return 1;
#endif

#ifdef IW_MODE_MONITOR
	ret = enter_rfmon_mode_wext(handle, sock_fd, device);
	if (ret < 0)
		return ret;
	if (ret == 1)
		return 1;
#endif


	return 0;
}
