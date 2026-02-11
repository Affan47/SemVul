find_mod_export(char* mod, char* name, int param_no, int flags)
{
	struct sr_module* t;
	cmd_export_t* cmd;

	for (t = modules; t; t = t->next) {
		if (strcmp(t->exports->name, mod) == 0) {
			for (cmd = t->exports->cmds;  cmd && cmd->name; cmd++) {
				if ((strcmp(name, cmd->name) == 0) &&
				    (cmd->param_no == param_no) &&
				    ((cmd->flags & flags) == flags)
				   ){
					LM_DBG("found <%s> in module %s [%s]\n",
					    name, t->exports->name, t->path);
					return cmd->function;
				}
			}
		}
	}

	LM_DBG("<%s> in module %s not found\n", name, mod);
	return 0;
}
