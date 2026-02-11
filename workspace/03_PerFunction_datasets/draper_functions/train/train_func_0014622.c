drbd_incoming_connection(struct sock *sk)
{
	struct accept_wait_data *ad = sk->sk_user_data;
	void (*state_change)(struct sock *sk);

	state_change = ad->original_sk_state_change;
	if (sk->sk_state == TCP_ESTABLISHED)
		complete(&ad->door_bell);
	state_change(sk);
}
