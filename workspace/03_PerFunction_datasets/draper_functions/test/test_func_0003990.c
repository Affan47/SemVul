sc_common_open(struct file *file, int ctxt)
{
	struct o2net_sock_debug *sd;
	struct o2net_sock_container *dummy_sc;

	dummy_sc = kzalloc(sizeof(*dummy_sc), GFP_KERNEL);
	if (!dummy_sc)
		return -ENOMEM;

	sd = __seq_open_private(file, &sc_seq_ops, sizeof(*sd));
	if (!sd) {
		kfree(dummy_sc);
		return -ENOMEM;
	}

	sd->dbg_ctxt = ctxt;
	sd->dbg_sock = dummy_sc;

	o2net_debug_add_sc(dummy_sc);

	return 0;
}
