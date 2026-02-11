putdb(void)
{
	void	*zp;
	int	scomp, ncomp;

	if (!super_mmapped && (sfp = dbfp(SUPER, O_WRONLY, &scomp, &sname))
			== NULL || sfp == (FILE *)-1)
		return;
	if (!nodes_mmapped && (nfp = dbfp(NODES, O_WRONLY, &ncomp, &nname))
			== NULL || nfp == (FILE *)-1)
		return;
	if (super_mmapped == 0 || nodes_mmapped == 0)
		holdint();


	if (super_mmapped)
		utime(sname, NULL);
	else if (scomp) {
		zp = zalloc(sfp);
		zwrite(zp, super, SIZEOF_super);
		zfree(zp);
		trunc(sfp);
	} else
		fwrite(super, 1, SIZEOF_super, sfp);
	if (nodes_mmapped)
		utime(nname, NULL);
	else if (ncomp) {
		zp = zalloc(nfp);
		zwrite(zp, nodes, getn(&super[OF_super_size]) * SIZEOF_node);
		zfree(zp);
		trunc(nfp);
	} else
		fwrite(nodes, 1,
			getn(&super[OF_super_size]) * SIZEOF_node, nfp);
	if (super_mmapped == 0 || nodes_mmapped == 0)
		relseint();
}
