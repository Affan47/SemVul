selinux_netlbl_sock_getattr(
							const struct sock *sk,
							u32 sid)
{
	struct sk_security_struct *sksec = sk->sk_security;
	struct netlbl_lsm_secattr *secattr = sksec->nlbl_secattr;

	if (secattr == NULL)
		return NULL;

	if ((secattr->flags & NETLBL_SECATTR_SECID) &&
	    (secattr->attr.secid == sid))
		return secattr;

	return NULL;
}
