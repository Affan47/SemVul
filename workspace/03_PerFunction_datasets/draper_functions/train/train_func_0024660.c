EmitFiniFunc(const struct vcc *tl)
{
	unsigned u;

	Fc(tl, 0, "\nstatic void\nVGC_Fini(struct cli *cli)\n{\n\n");


	for (u = 0; u < tl->nvmodpriv; u++)
		Fc(tl, 0, "\tvmod_priv_fini(&vmod_priv_%u);\n", u);

	AZ(VSB_finish(tl->ff));
	VSB_cat(tl->fc, VSB_data(tl->ff));
	Fc(tl, 0, "}\n");
}
