cosm_set_time(struct cosm_msg *msg)
{
	int rc = do_settimeofday64(&msg->timespec);

	if (rc)
		dev_err(&client_spdev->dev, "%s: %d settimeofday rc %d\n",
			__func__, __LINE__, rc);
}
