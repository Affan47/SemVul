gf_sg_mfstring_del(MFString par)
{
	u32 i;
	for (i=0; i<par.count; i++) {
		if (par.vals[i]) gf_free(par.vals[i]);
	}
	gf_free(par.vals);
}
