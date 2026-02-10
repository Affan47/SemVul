update_option(const char *this, char *val, int flags)
{
	struct opt_list *po;

	SLIST_FOREACH(po, &otab, o_next) {
		if (eq(po->o_name, this)) {
			free(po->o_file);
			po->o_file = val;
			po->o_flags = flags;
			return;
		}
	}


	return;
}
