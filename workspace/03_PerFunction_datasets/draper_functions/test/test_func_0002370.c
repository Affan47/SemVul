get_rndis_request(struct rndis_device *dev,
					     u32 msg_type,
					     u32 msg_len)
{
	struct rndis_request *request;
	struct rndis_message *rndis_msg;
	struct rndis_set_request *set;
	unsigned long flags;

	request = kzalloc(sizeof(struct rndis_request), GFP_KERNEL);
	if (!request)
		return NULL;

	init_completion(&request->wait_event);

	rndis_msg = &request->request_msg;
	rndis_msg->ndis_msg_type = msg_type;
	rndis_msg->msg_len = msg_len;

	request->pkt.q_idx = 0;


	set = &rndis_msg->msg.set_req;
	set->req_id = atomic_inc_return(&dev->new_req_id);


	spin_lock_irqsave(&dev->request_lock, flags);
	list_add_tail(&request->list_ent, &dev->req_list);
	spin_unlock_irqrestore(&dev->request_lock, flags);

	return request;
}
