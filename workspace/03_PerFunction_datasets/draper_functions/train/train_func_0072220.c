ssp_clean_pending_list(struct ssp_data *data)
{
	struct ssp_msg *msg, *n;

	mutex_lock(&data->pending_lock);
	list_for_each_entry_safe(msg, n, &data->pending_list, list) {
		list_del(&msg->list);

		if (msg->done)
			if (!completion_done(msg->done))
				complete(msg->done);
	}
	mutex_unlock(&data->pending_lock);
}
