ath10k_wmi_op_pull_vdev_start_ev(struct ath10k *ar, struct sk_buff *skb,
				 struct wmi_vdev_start_ev_arg *arg)
{
	struct wmi_vdev_start_response_event *ev = (void *)skb->data;

	if (skb->len < sizeof(*ev))
		return -EPROTO;

	skb_pull(skb, sizeof(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->req_id = ev->req_id;
	arg->resp_type = ev->resp_type;
	arg->status = ev->status;

	return 0;
}
