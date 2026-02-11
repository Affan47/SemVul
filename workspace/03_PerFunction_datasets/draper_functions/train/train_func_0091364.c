isl_printer_yaml_end_sequence(
	__isl_take isl_printer *p)
{
	enum isl_yaml_state state, up;

	state = current_state(p);
	p = pop_state(p);
	if (!p)
		return NULL;
	if (p->yaml_style == ISL_YAML_STYLE_FLOW)
		return p->ops->print_str(p, " ]");
	up = current_state(p);
	if (state == isl_yaml_sequence_first_start) {
		if (up == isl_yaml_mapping_val)
			p = p->ops->print_str(p, " []");
		else
			p = p->ops->print_str(p, "[]");
	} else {
		p = isl_printer_indent(p, -2);
	}
	if (!p)
		return NULL;
	state = current_state(p);
	if (state == isl_yaml_none)
		p = p->ops->end_line(p);
	return p;
}
