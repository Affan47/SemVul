wl3501_set_nick(struct net_device *dev, struct iw_request_info *info,
			   union iwreq_data *wrqu, char *extra)
{
	struct wl3501_card *this = netdev_priv(dev);

	if (wrqu->data.length > sizeof(this->nick))
		return -E2BIG;
	strlcpy(this->nick, extra, wrqu->data.length);
	return 0;
}
