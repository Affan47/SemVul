pq_init(int node, int pnode)
{
	int cpu;
	size_t plsize;
	char *cp;
	void *vp;
	unsigned long pn;
	unsigned long first;
	unsigned long pn_first;
	unsigned long last;
	struct bau_pq_entry *pqp;
	struct bau_control *bcp;

	plsize = (DEST_Q_SIZE + 1) * sizeof(struct bau_pq_entry);
	vp = kmalloc_node(plsize, GFP_KERNEL, node);
	pqp = (struct bau_pq_entry *)vp;
	BUG_ON(!pqp);

	cp = (char *)pqp + 31;
	pqp = (struct bau_pq_entry *)(((unsigned long)cp >> 5) << 5);

	for_each_present_cpu(cpu) {
		if (pnode != uv_cpu_to_pnode(cpu))
			continue;

		bcp = &per_cpu(bau_control, cpu);
		bcp->queue_first	= pqp;
		bcp->bau_msg_head	= pqp;
		bcp->queue_last		= pqp + (DEST_Q_SIZE - 1);
	}


	pn = uv_gpa_to_gnode(uv_gpa(pqp));
	first = uv_physnodeaddr(pqp);
	pn_first = ((unsigned long)pn << UV_PAYLOADQ_PNODE_SHIFT) | first;
	last = uv_physnodeaddr(pqp + (DEST_Q_SIZE - 1));
	write_mmr_payload_first(pnode, pn_first);
	write_mmr_payload_tail(pnode, first);
	write_mmr_payload_last(pnode, last);
	write_gmmr_sw_ack(pnode, 0xffffUL);


	memset(pqp, 0, sizeof(struct bau_pq_entry) * DEST_Q_SIZE);
}
