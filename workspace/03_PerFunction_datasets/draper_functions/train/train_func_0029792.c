bfa_sgpg_attach(struct bfa_s *bfa, void *bfad, struct bfa_iocfc_cfg_s *cfg,
		struct bfa_pcidev_s *pcidev)
{
	struct bfa_sgpg_mod_s *mod = BFA_SGPG_MOD(bfa);
	struct bfa_sgpg_s *hsgpg;
	struct bfi_sgpg_s *sgpg;
	u64 align_len;
	struct bfa_mem_dma_s *seg_ptr;
	u32	sgpg_sz = sizeof(struct bfi_sgpg_s);
	u16	i, idx, nsegs, per_seg_sgpg, num_sgpg;

	union {
		u64 pa;
		union bfi_addr_u addr;
	} sgpg_pa, sgpg_pa_tmp;

	INIT_LIST_HEAD(&mod->sgpg_q);
	INIT_LIST_HEAD(&mod->sgpg_wait_q);

	bfa_trc(bfa, cfg->drvcfg.num_sgpgs);

	mod->free_sgpgs = mod->num_sgpgs = cfg->drvcfg.num_sgpgs;

	num_sgpg = cfg->drvcfg.num_sgpgs;
	nsegs = BFI_MEM_DMA_NSEGS(num_sgpg, sgpg_sz);


	hsgpg = (struct bfa_sgpg_s *) bfa_mem_kva_curp(mod);

	bfa_mem_dma_seg_iter(mod, seg_ptr, nsegs, idx) {

		if (!bfa_mem_dma_virt(seg_ptr))
			break;

		align_len = BFA_SGPG_ROUNDUP(bfa_mem_dma_phys(seg_ptr)) -
					     bfa_mem_dma_phys(seg_ptr);

		sgpg = (struct bfi_sgpg_s *)
			(((u8 *) bfa_mem_dma_virt(seg_ptr)) + align_len);
		sgpg_pa.pa = bfa_mem_dma_phys(seg_ptr) + align_len;
		WARN_ON(sgpg_pa.pa & (sgpg_sz - 1));

		per_seg_sgpg = (seg_ptr->mem_len - (u32)align_len) / sgpg_sz;

		for (i = 0; num_sgpg > 0 && i < per_seg_sgpg; i++, num_sgpg--) {
			memset(hsgpg, 0, sizeof(*hsgpg));
			memset(sgpg, 0, sizeof(*sgpg));

			hsgpg->sgpg = sgpg;
			sgpg_pa_tmp.pa = bfa_sgaddr_le(sgpg_pa.pa);
			hsgpg->sgpg_pa = sgpg_pa_tmp.addr;
			list_add_tail(&hsgpg->qe, &mod->sgpg_q);

			sgpg++;
			hsgpg++;
			sgpg_pa.pa += sgpg_sz;
		}
	}

	bfa_mem_kva_curp(mod) = (u8 *) hsgpg;
}
