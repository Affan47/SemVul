disconnect_request(struct radius_pd_t *rpd)
{
	if (conf_verbose) {
		log_ppp_info2("recv ");
		rad_packet_print(rpd->dm_coa_req, NULL, log_ppp_info2);
	}

	dm_coa_send_ack(serv.hnd.fd, rpd->dm_coa_req, &rpd->dm_coa_addr);

	rad_packet_free(rpd->dm_coa_req);

	pthread_mutex_lock(&rpd->lock);
	rpd->dm_coa_req = NULL;
	pthread_mutex_unlock(&rpd->lock);

	ap_session_terminate(rpd->ses, TERM_ADMIN_RESET, 0);
}
