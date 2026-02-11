seq_open_net(struct inode *ino, struct file *f,
		 const struct seq_operations *ops, int size)
{
	struct net *net;
	struct seq_net_private *p;

	BUG_ON(size < sizeof(*p));

	net = get_proc_net(ino);
	if (net == NULL)
		return -ENXIO;

	p = __seq_open_private(f, ops, size);
	if (p == NULL) {
		put_net(net);
		return -ENOMEM;
	}
#ifdef CONFIG_NET_NS
	p->net = net;
#endif
	return 0;
}
