open_policy_init_values(struct open_policy *op, const apol_policy_path_t * orig_path,
				    const apol_policy_path_t * mod_path)
{
	if (orig_path != NULL) {
		open_policy_init_value(op, orig_path, op->pane + SEDIFFX_POLICY_ORIG);
	}
	if (mod_path != NULL) {
		open_policy_init_value(op, mod_path, op->pane + SEDIFFX_POLICY_MOD);
	}
}
