output_goto (struct cb_goto *p)
{
	cb_tree l;
	int	i = 1;

	if (p->depending) {
		output_prefix ();
		output ("switch (");
		output_param (cb_build_cast_integer (p->depending), 0);
		output (")\n");
		output_indent ("  {");
		for (l = p->target; l; l = CB_CHAIN (l)) {
			output_indent_level -= 2;
			output_line ("case %d:", i++);
			output_indent_level += 2;
			output_goto_1 (CB_VALUE (l));
		}
		output_indent ("  }");
	} else if (p->target == NULL) {
		needs_exit_prog = 1;
		if (cb_flag_implicit_init) {
			output_line ("goto exit_program;");
		} else {
			output_line ("if (module.next)");
			output_line ("  goto exit_program;");
		}
	} else if (p->target == cb_int1) {
		needs_exit_prog = 1;
		output_line ("goto exit_program;");
	} else {
		output_goto_1 (p->target);
	}
}
