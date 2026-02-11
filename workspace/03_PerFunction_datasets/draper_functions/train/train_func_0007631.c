grow(unsigned long size)
{
	unsigned long	incr, newsize;
	void	*onodes;

	incr = size > MAX2 ? MAX2 : size;
	newsize = size + incr;
	if (newsize > MAX4-MAX2) {
	oflo:	fprintf(stderr, "Junk mail database overflow.\n");
		return 0;
	}
	if (nodes_mmapped) {
		if (lseek(fileno(nfp), newsize*SIZEOF_node-1, SEEK_SET)
				== (off_t)-1 || write(fileno(nfp),"\0",1) != 1)
			goto oflo;
		onodes = nodes;
		if ((nodes = mremap(nodes, nodes_mmapped, newsize*SIZEOF_node,
				MREMAP_MAYMOVE)) == MAP_FAILED) {
			if ((nodes = mmap(NULL, newsize*SIZEOF_node,
						rw_map!=O_RDONLY ?
							PROT_READ|PROT_WRITE :
							PROT_READ,
						MAP_SHARED, fileno(nfp), 0))
					== MAP_FAILED) {
				nodes = onodes;
				goto oflo;
			}
			munmap(onodes, nodes_mmapped);
		}
		nodes_mmapped = newsize*SIZEOF_node;
	} else {
		nodes = srealloc(nodes, newsize*SIZEOF_node);
		memset(&nodes[size*SIZEOF_node], 0, incr*SIZEOF_node);
	}
	size = newsize;
	putn(&super[OF_super_size], size);
	return size;
}
