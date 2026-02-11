geneve_find_sock(struct geneve_net *gn,
					    sa_family_t family,
					    __be16 dst_port)
{
	struct geneve_sock *gs;

	list_for_each_entry(gs, &gn->sock_list, list) {
		if (inet_sk(gs->sock->sk)->inet_sport == dst_port &&
		    inet_sk(gs->sock->sk)->sk.sk_family == family) {
			return gs;
		}
	}
	return NULL;
}
