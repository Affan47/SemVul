brcmf_msgbuf_process_ioctl_complete(struct brcmf_msgbuf *msgbuf, void *buf)
{
	struct msgbuf_ioctl_resp_hdr *ioctl_resp;

	ioctl_resp = (struct msgbuf_ioctl_resp_hdr *)buf;

	msgbuf->ioctl_resp_status =
			(s16)le16_to_cpu(ioctl_resp->compl_hdr.status);
	msgbuf->ioctl_resp_ret_len = le16_to_cpu(ioctl_resp->resp_len);
	msgbuf->ioctl_resp_pktid = le32_to_cpu(ioctl_resp->msg.request_id);

	brcmf_msgbuf_ioctl_resp_wake(msgbuf);

	if (msgbuf->cur_ioctlrespbuf)
		msgbuf->cur_ioctlrespbuf--;
	brcmf_msgbuf_rxbuf_ioctlresp_post(msgbuf);
}
