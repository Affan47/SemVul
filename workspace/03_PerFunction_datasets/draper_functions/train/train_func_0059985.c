r600_dma_cs_next_reloc(struct radeon_cs_parser *p,
			   struct radeon_bo_list **cs_reloc)
{
	struct radeon_cs_chunk *relocs_chunk;
	unsigned idx;

	*cs_reloc = NULL;
	if (p->chunk_relocs == NULL) {
		DRM_ERROR("No relocation chunk !\n");
		return -EINVAL;
	}
	relocs_chunk = p->chunk_relocs;
	idx = p->dma_reloc_idx;
	if (idx >= p->nrelocs) {
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, p->nrelocs);
		return -EINVAL;
	}
	*cs_reloc = &p->relocs[idx];
	p->dma_reloc_idx++;
	return 0;
}
