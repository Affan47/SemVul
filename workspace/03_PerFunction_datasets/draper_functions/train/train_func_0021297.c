__team_option_inst_mark_removed_port(struct team *team,
						 struct team_port *port)
{
	struct team_option_inst *opt_inst;

	list_for_each_entry(opt_inst, &team->option_inst_list, list) {
		if (opt_inst->info.port == port) {
			opt_inst->changed = true;
			opt_inst->removed = true;
		}
	}
}
