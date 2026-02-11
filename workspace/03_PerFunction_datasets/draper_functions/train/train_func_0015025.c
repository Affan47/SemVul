bnad_mem_alloc(struct bnad *bnad,
	       struct bna_mem_info *mem_info)
{
	int i;
	dma_addr_t dma_pa;

	if ((mem_info->num == 0) || (mem_info->len == 0)) {
		mem_info->mdl = NULL;
		return 0;
	}

	mem_info->mdl = kcalloc(mem_info->num, sizeof(struct bna_mem_descr),
				GFP_KERNEL);
	if (mem_info->mdl == NULL)
		return -ENOMEM;

	if (mem_info->mem_type == BNA_MEM_T_DMA) {
		for (i = 0; i < mem_info->num; i++) {
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva =
				dma_alloc_coherent(&bnad->pcidev->dev,
						   mem_info->len, &dma_pa,
						   GFP_KERNEL);
			if (mem_info->mdl[i].kva == NULL)
				goto err_return;

			BNA_SET_DMA_ADDR(dma_pa,
					 &(mem_info->mdl[i].dma));
		}
	} else {
		for (i = 0; i < mem_info->num; i++) {
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva = kzalloc(mem_info->len,
							GFP_KERNEL);
			if (mem_info->mdl[i].kva == NULL)
				goto err_return;
		}
	}

	return 0;

err_return:
	bnad_mem_free(bnad, mem_info);
	return -ENOMEM;
}
