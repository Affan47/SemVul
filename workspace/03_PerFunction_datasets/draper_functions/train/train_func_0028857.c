ql_check_lb_frame(struct ql_adapter *qdev,
					struct sk_buff *skb)
{
	unsigned int frame_size = skb->len;

	if ((*(skb->data + 3) == 0xFF) &&
		(*(skb->data + frame_size / 2 + 10) == 0xBE) &&
		(*(skb->data + frame_size / 2 + 12) == 0xAF)) {
			atomic_dec(&qdev->lb_count);
			return;
	}
}
