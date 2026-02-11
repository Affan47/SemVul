tcsd_set_remote_op(struct tcsd_config *conf, char *op_name)
{
	int i = 0;

	while(tcsd_ops[i]) {
		if (!strcasecmp(tcsd_ops[i]->name, op_name)) {

			tcsd_add_op(conf->remote_ops, tcsd_ops[i]->op);
			return 0;
		}
		i++;
	}


	return 1;
}
