vrrp_mcast_group4_handler(vector_t *strvec)
{
	struct sockaddr_storage *mcast = &global_data->vrrp_mcast_group4;
	int ret;

	ret = inet_stosockaddr(vector_slot(strvec, 1), 0, mcast);
	if (ret < 0) {
		log_message(LOG_ERR, "Configuration error: Cant parse vrrp_mcast_group4 [%s]. Skipping"
				   , vector_slot(strvec, 1));
	}
}
