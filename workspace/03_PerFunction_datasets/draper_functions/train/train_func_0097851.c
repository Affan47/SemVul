selinux_xfrm_skb_sid(struct sk_buff *skb, u32 *sid)
{
	int rc;

	rc = selinux_xfrm_skb_sid_ingress(skb, sid, 0);
	if (rc == 0 && *sid == SECSID_NULL)
		*sid = selinux_xfrm_skb_sid_egress(skb);

	return rc;
}
