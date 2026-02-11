nic_enable(nic_t *nic)
{
	if (nic->flags & NIC_GOING_DOWN) {
		LOG_INFO(PFX "%s: NIC device is going down, "
			 "flag: 0x%x state: 0x%x",
			 nic->log_name, nic->flags, nic->state);
		return -EINVAL;
	}
	if (nic->state == NIC_STOPPED) {
		struct timespec ts;
		struct timeval tp;
		int rc;

		pthread_mutex_lock(&nic->nic_mutex);

		pthread_cond_broadcast(&nic->enable_wait_cond);

		nic->flags &= ~NIC_DISABLED;
		nic->flags |= NIC_ENABLED;
		nic->flags |= NIC_ENABLED_PENDING;


		rc = gettimeofday(&tp, NULL);
		ts.tv_sec = tp.tv_sec;
		ts.tv_nsec = tp.tv_usec * 1000;
		ts.tv_sec += 100;


		rc = pthread_cond_timedwait(&nic->enable_done_cond,
					    &nic->nic_mutex, &ts);
		if (rc == 0 && nic->flags & NIC_ENABLED) {
			LOG_DEBUG(PFX "%s: device enabled", nic->log_name);
		} else {
			nic->flags &= ~NIC_ENABLED;
			nic->flags |= NIC_DISABLED;
			nic->flags &= ~NIC_ENABLED_PENDING;

			LOG_ERR(PFX "%s: waiting to finish nic_enable err: %s",
				nic->log_name, strerror(rc));
		}
		pthread_mutex_unlock(&nic->nic_mutex);

		return rc;
	} else {
		LOG_INFO(PFX "%s: device already enabled: "
			 "flag: 0x%x state: 0x%x",
			 nic->log_name, nic->flags, nic->state);
		return -EALREADY;
	}
}
