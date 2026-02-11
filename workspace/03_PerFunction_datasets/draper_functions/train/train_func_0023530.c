sc_show_sock_container(struct seq_file *seq,
				   struct o2net_sock_container *sc)
{
	struct inet_sock *inet = NULL;
	__be32 saddr = 0, daddr = 0;
	__be16 sport = 0, dport = 0;

	if (!sc)
		return;

	if (sc->sc_sock) {
		inet = inet_sk(sc->sc_sock->sk);

		saddr = (__force __be32)inet->inet_saddr;
		daddr = (__force __be32)inet->inet_daddr;
		sport = (__force __be16)inet->inet_sport;
		dport = (__force __be16)inet->inet_dport;
	}


	seq_printf(seq, "%p:\n"
		   "  krefs:           %d\n"
		   "  sock:            %pI4:%u -> "
				      "%pI4:%u\n"
		   "  remote node:     %s\n"
		   "  page off:        %zu\n"
		   "  handshake ok:    %u\n"
		   "  timer:           %lld usecs\n"
		   "  data ready:      %lld usecs\n"
		   "  advance start:   %lld usecs\n"
		   "  advance stop:    %lld usecs\n"
		   "  func start:      %lld usecs\n"
		   "  func stop:       %lld usecs\n"
		   "  func key:        0x%08x\n"
		   "  func type:       %u\n",
		   sc,
		   atomic_read(&sc->sc_kref.refcount),
		   &saddr, inet ? ntohs(sport) : 0,
		   &daddr, inet ? ntohs(dport) : 0,
		   sc->sc_node->nd_name,
		   sc->sc_page_off,
		   sc->sc_handshake_ok,
		   (long long)ktime_to_us(sc->sc_tv_timer),
		   (long long)ktime_to_us(sc->sc_tv_data_ready),
		   (long long)ktime_to_us(sc->sc_tv_advance_start),
		   (long long)ktime_to_us(sc->sc_tv_advance_stop),
		   (long long)ktime_to_us(sc->sc_tv_func_start),
		   (long long)ktime_to_us(sc->sc_tv_func_stop),
		   sc->sc_msg_key,
		   sc->sc_msg_type);
}
