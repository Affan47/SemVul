mgt_vcc_default(const char *b_arg, const char *f_arg, char *vcl, int C_flag)
{
	char *vf;
	struct vsb *sb;
	struct vclprog *vp;
	char buf[BUFSIZ];


	(void)f_arg;

	if (b_arg != NULL) {
		AZ(vcl);


		bprintf(buf,
		    "backend default {\n"
		    "    .host = \"%s\";\n"
		    "}\n", b_arg);
		vcl = strdup(buf);
		AN(vcl);
	}
	strcpy(buf, "boot");

	vf = mgt_VccCompile(&sb, vcl, C_flag);
	free(vcl);
	if (VSB_len(sb) > 0)
		fprintf(stderr, "%s", VSB_data(sb));
	VSB_delete(sb);
	if (C_flag) {
		if (vf != NULL)
			AZ(unlink(vf));
		return (0);
	}
	if (vf == NULL) {
		fprintf(stderr, "\nVCL compilation failed\n");
		return (1);
	}
	vp = mgt_vcc_add(buf, vf);
	vp->active = 1;
	return (0);
}
