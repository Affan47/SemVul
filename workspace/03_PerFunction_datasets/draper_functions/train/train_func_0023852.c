nv41_vm_map_sg(struct nvkm_vma *vma, struct nvkm_memory *pgt,
	       struct nvkm_mem *mem, u32 pte, u32 cnt, dma_addr_t *list)
{
	pte = pte * 4;
	nvkm_kmap(pgt);
	while (cnt) {
		u32 page = PAGE_SIZE / NV41_GART_PAGE;
		u64 phys = (u64)*list++;
		while (cnt && page--) {
			nvkm_wo32(pgt, pte, (phys >> 7) | 1);
			phys += NV41_GART_PAGE;
			pte += 4;
			cnt -= 1;
		}
	}
	nvkm_done(pgt);
}
