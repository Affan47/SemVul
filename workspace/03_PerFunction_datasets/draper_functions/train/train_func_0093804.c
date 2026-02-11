drop_ike_sa_init(private_receiver_t *this, message_t *message)
{
	u_int half_open;
	u_int32_t now;

	now = time_monotonic(NULL);
	half_open = charon->ike_sa_manager->get_half_open_count(
										charon->ike_sa_manager, NULL);


	if (message->get_major_version(message) == IKEV2_MAJOR_VERSION &&
		cookie_required(this, half_open, now) && !check_cookie(this, message))
	{
		chunk_t cookie;

		DBG2(DBG_NET, "received packet from: %#H to %#H",
			 message->get_source(message),
			 message->get_destination(message));
		if (!cookie_build(this, message, now - this->secret_offset,
						  chunk_from_thing(this->secret), &cookie))
		{
			return TRUE;
		}
		DBG2(DBG_NET, "sending COOKIE notify to %H",
			 message->get_source(message));
		send_notify(message, IKEV2_MAJOR_VERSION, IKE_SA_INIT, COOKIE, cookie);
		chunk_free(&cookie);
		if (++this->secret_used > COOKIE_REUSE)
		{
			char secret[SECRET_LENGTH];

			DBG1(DBG_NET, "generating new cookie secret after %d uses",
				 this->secret_used);
			if (this->rng->get_bytes(this->rng, SECRET_LENGTH, secret))
			{
				memcpy(this->secret_old, this->secret, SECRET_LENGTH);
				memcpy(this->secret, secret, SECRET_LENGTH);
				memwipe(secret, SECRET_LENGTH);
				this->secret_switch = now;
				this->secret_used = 0;
			}
			else
			{
				DBG1(DBG_NET, "failed to allocated cookie secret, keeping old");
			}
		}
		return TRUE;
	}


	if (this->block_threshold &&
		charon->ike_sa_manager->get_half_open_count(charon->ike_sa_manager,
				message->get_source(message)) >= this->block_threshold)
	{
		DBG1(DBG_NET, "ignoring IKE_SA setup from %H, "
			 "peer too aggressive", message->get_source(message));
		return TRUE;
	}


	if (this->init_limit_half_open &&
		half_open >= this->init_limit_half_open)
	{
		DBG1(DBG_NET, "ignoring IKE_SA setup from %H, half open IKE_SA "
			 "count of %d exceeds limit of %d", message->get_source(message),
			 half_open, this->init_limit_half_open);
		return TRUE;
	}


	if (this->init_limit_job_load)
	{
		u_int jobs = 0, i;

		for (i = 0; i < JOB_PRIO_MAX; i++)
		{
			jobs += lib->processor->get_job_load(lib->processor, i);
		}
		if (jobs > this->init_limit_job_load)
		{
			DBG1(DBG_NET, "ignoring IKE_SA setup from %H, job load of %d "
				 "exceeds limit of %d", message->get_source(message),
				 jobs, this->init_limit_job_load);
			return TRUE;
		}
	}
	return FALSE;
}
