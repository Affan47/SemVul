pan_vcl(const struct VCL_conf *vcl)
{
	int i;

	VSB_printf(pan_vsp, "    vcl = {\n");
	VSB_printf(pan_vsp, "      srcname = {\n");
	for (i = 0; i < vcl->nsrc; ++i)
		VSB_printf(pan_vsp, "        \"%s\",\n", vcl->srcname[i]);
	VSB_printf(pan_vsp, "      },\n");
	VSB_printf(pan_vsp, "    },\n");
}
