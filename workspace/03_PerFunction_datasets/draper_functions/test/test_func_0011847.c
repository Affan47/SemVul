_vcfree(void)
{
	int4		i;
	struct vcdesc	*p;


	f_init = 1;

	for (i = 0, p = vctable; i < VCMAX; ++i, ++p) {
		p->vc_node = NOTNODEID;
		close(p->vc_path);
	}

}
