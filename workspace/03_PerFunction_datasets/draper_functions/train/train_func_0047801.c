EmitInitFunc(const struct vcc *tl)
{

	Fc(tl, 0, "\nstatic int\nVGC_Init(struct cli *cli)\n{\n\n");
	AZ(VSB_finish(tl->fi));
	VSB_cat(tl->fc, VSB_data(tl->fi));
	Fc(tl, 0, "\treturn(0);\n");
	Fc(tl, 0, "}\n");
}
