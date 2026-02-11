o_getconfig(void)
{
	int type;
	VALUE *vp;

	vp = &stack[0];
	if (vp->v_type == V_ADDR)
		vp = vp->v_addr;
	if (vp->v_type != V_STR) {
		math_error("Non-string for config");

	}
	type = configtype(vp->v_str->s_str);
	if (type < 0) {
		math_error("Unknown config name \"%s\"",
			vp->v_str->s_str);

	}
	freevalue(stack);
	config_value(conf, type, stack);
}
