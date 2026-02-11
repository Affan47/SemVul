c2_reg_phys_mr(struct ib_pd *ib_pd,
				    struct ib_phys_buf *buffer_list,
				    int num_phys_buf, int acc, u64 * iova_start)
{
	struct c2_mr *mr;
	u64 *page_list;
	u32 total_len;
	int err, i, j, k, page_shift, pbl_depth;

	pbl_depth = 0;
	total_len = 0;

	page_shift = PAGE_SHIFT;


	if (num_phys_buf == 1)
		page_shift += 3;

	for (i = 0; i < num_phys_buf; i++) {

		if (offset_in_page(buffer_list[i].addr)) {
			pr_debug("Unaligned Memory Buffer: 0x%x\n",
				(unsigned int) buffer_list[i].addr);
			return ERR_PTR(-EINVAL);
		}

		if (!buffer_list[i].size) {
			pr_debug("Invalid Buffer Size\n");
			return ERR_PTR(-EINVAL);
		}

		total_len += buffer_list[i].size;
		pbl_depth += ALIGN(buffer_list[i].size,
				   BIT(page_shift)) >> page_shift;
	}

	page_list = vmalloc(sizeof(u64) * pbl_depth);
	if (!page_list) {
		pr_debug("couldn't vmalloc page_list of size %zd\n",
			(sizeof(u64) * pbl_depth));
		return ERR_PTR(-ENOMEM);
	}

	for (i = 0, j = 0; i < num_phys_buf; i++) {

		int naddrs;

 		naddrs = ALIGN(buffer_list[i].size,
			       BIT(page_shift)) >> page_shift;
		for (k = 0; k < naddrs; k++)
			page_list[j++] = (buffer_list[i].addr +
						     (k << page_shift));
	}

	mr = kmalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr) {
		vfree(page_list);
		return ERR_PTR(-ENOMEM);
	}

	mr->pd = to_c2pd(ib_pd);
	mr->umem = NULL;
	pr_debug("%s - page shift %d, pbl_depth %d, total_len %u, "
		"*iova_start %llx, first pa %llx, last pa %llx\n",
		__func__, page_shift, pbl_depth, total_len,
		(unsigned long long) *iova_start,
	       	(unsigned long long) page_list[0],
	       	(unsigned long long) page_list[pbl_depth-1]);
  	err = c2_nsmr_register_phys_kern(to_c2dev(ib_pd->device), page_list,
					 BIT(page_shift), pbl_depth,
					 total_len, 0, iova_start,
					 c2_convert_access(acc), mr);
	vfree(page_list);
	if (err) {
		kfree(mr);
		return ERR_PTR(err);
	}

	return &mr->ibmr;
}
