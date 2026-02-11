tcpconn_add(struct tcp_connection *c)
{
	unsigned hash;

	if (c){
		TCPCONN_LOCK;

		hash=tcp_id_hash(c->id);
		c->id_hash=hash;
		tcpconn_listadd(tcpconn_id_hash[hash], c, id_next, id_prev);

		hash=tcp_addr_hash(&c->rcv.src_ip, c->rcv.src_port);

		c->con_aliases[0].port=c->rcv.src_port;
		c->con_aliases[0].hash=hash;
		c->con_aliases[0].parent=c;
		tcpconn_listadd(tcpconn_aliases_hash[hash], &c->con_aliases[0],
						next, prev);
		c->aliases++;
		TCPCONN_UNLOCK;
		LM_DBG("hashes: %d, %d\n", hash, c->id_hash);
		return c;
	}else{
		LM_CRIT("null connection pointer\n");
		return 0;
	}
}
