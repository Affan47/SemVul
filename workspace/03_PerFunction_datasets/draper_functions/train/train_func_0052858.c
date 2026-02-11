smack_netlabel(struct sock *sk, int labeled)
{
	struct smack_known *skp;
	struct socket_smack *ssp = sk->sk_security;
	int rc = 0;


	local_bh_disable();
	bh_lock_sock_nested(sk);

	if (ssp->smk_out == smack_net_ambient ||
	    labeled == SMACK_UNLABELED_SOCKET)
		netlbl_sock_delattr(sk);
	else {
		skp = ssp->smk_out;
		rc = netlbl_sock_setattr(sk, sk->sk_family, &skp->smk_netlabel);
	}

	bh_unlock_sock(sk);
	local_bh_enable();

	return rc;
}
