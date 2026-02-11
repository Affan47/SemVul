relsedb(void)
{
	if (super_mmapped) {
		munmap(super, super_mmapped);
		super_mmapped = 0;
	} else
		free(super);
	if (nodes_mmapped) {
		munmap(nodes, nodes_mmapped);
		nodes_mmapped = 0;
	} else
		free(nodes);
	if (sfp && sfp != (FILE *)-1) {
		Fclose(sfp);
		sfp = NULL;
	}
	if (nfp && nfp != (FILE *)-1) {
		Fclose(nfp);
		nfp = NULL;
	}
}
