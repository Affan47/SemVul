hpsa_drain_accel_commands(struct ctlr_info *h)
{
	struct CommandList *c = NULL;
	int i, accel_cmds_out;
	int refcount;

	do {
		accel_cmds_out = 0;
		for (i = 0; i < h->nr_cmds; i++) {
			c = h->cmd_pool + i;
			refcount = atomic_inc_return(&c->refcount);
			if (refcount > 1)
				accel_cmds_out += is_accelerated_cmd(c);
			cmd_free(h, c);
		}
		if (accel_cmds_out <= 0)
			break;
		msleep(100);
	} while (1);
}
