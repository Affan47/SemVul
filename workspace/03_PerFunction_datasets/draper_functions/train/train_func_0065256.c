ixgb_check_copybreak(struct napi_struct *napi,
				 struct ixgb_buffer *buffer_info,
				 u32 length, struct sk_buff **skb)
{
	struct sk_buff *new_skb;

	if (length > copybreak)
		return;

	new_skb = napi_alloc_skb(napi, length);
	if (!new_skb)
		return;

	skb_copy_to_linear_data_offset(new_skb, -NET_IP_ALIGN,
				       (*skb)->data - NET_IP_ALIGN,
				       length + NET_IP_ALIGN);

	buffer_info->skb = *skb;
	*skb = new_skb;
}
