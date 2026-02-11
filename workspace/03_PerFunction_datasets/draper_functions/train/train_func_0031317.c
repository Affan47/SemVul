s3fwrn5_fw_prep_msg(struct s3fwrn5_fw_info *fw_info,
	struct sk_buff **msg, u8 type, u8 code, const void *data, u16 len)
{
	struct s3fwrn5_fw_header hdr;
	struct sk_buff *skb;

	hdr.type = type | fw_info->parity;
	fw_info->parity ^= 0x80;
	hdr.code = code;
	hdr.len = len;

	skb = alloc_skb(S3FWRN5_FW_HDR_SIZE + len, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	memcpy(skb_put(skb, S3FWRN5_FW_HDR_SIZE), &hdr, S3FWRN5_FW_HDR_SIZE);
	if (len)
		memcpy(skb_put(skb, len), data, len);

	*msg = skb;

	return 0;
}
