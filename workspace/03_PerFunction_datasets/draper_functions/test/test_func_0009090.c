strategy_deny_length(enum grecs_callback_command cmd,
		     grecs_locus_t *locus,
		     dico_list_t list,
		     grecs_value_t *value,
		     enum cmp_op op)
{
    if (cmd != grecs_callback_set_value) {
	grecs_error(locus, 0, _("Unexpected block statement"));
	return 0;
    }
    if (value->type == GRECS_TYPE_STRING) {
	size_t val;

	if (grecs_string_convert(&val, grecs_type_size,
				 value->v.string, locus))
	    return 0;
	stratcl_add_cmp(list, op, val);
    } else
	grecs_error(locus, 0, _("Expected number"));
    return 0;
}
