dbg_meas(const char *name)
{
	const struct obj *obj;
	const struct inst *inst;
	struct coord a1, b1;
	char *s;

	obj = find_obj(frames, name);
	if (!obj) {
		yyerrorf("unknown object \"%s\"", name);
		return 0;
	}


	if (!pkg_name)
                pkg_name = stralloc("_");
        reporter = report_to_stderr;
	if (!instantiate())
		return 0;

	inst = find_meas_hint(obj);
	if (!inst) {
		yyerrorf("measurement \"%s\" was not instantiated", name);
		return 0;
	}

	project_meas(inst, &a1, &b1);
	s = format_len(obj->u.meas.label ? obj->u.meas.label : "",
	    dist_point(a1, b1), curr_unit);
	printf("%s\n", s);
	free(s);

	return 1;
}
