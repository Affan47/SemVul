__hugetlb_alloc_buddy_huge_page(struct hstate *h,
		struct vm_area_struct *vma, unsigned long addr, int nid)
{
	int order = huge_page_order(h);
	gfp_t gfp = htlb_alloc_mask(h)|__GFP_COMP|__GFP_REPEAT|__GFP_NOWARN;
	unsigned int cpuset_mems_cookie;


	if (!IS_ENABLED(CONFIG_NUMA) || !vma) {


		if (nid != NUMA_NO_NODE)
			gfp |= __GFP_THISNODE;


		return alloc_pages_node(nid, gfp, order);
	}


	do {
		struct page *page;
		struct mempolicy *mpol;
		struct zonelist *zl;
		nodemask_t *nodemask;

		cpuset_mems_cookie = read_mems_allowed_begin();
		zl = huge_zonelist(vma, addr, gfp, &mpol, &nodemask);
		mpol_cond_put(mpol);
		page = __alloc_pages_nodemask(gfp, order, zl, nodemask);
		if (page)
			return page;
	} while (read_mems_allowed_retry(cpuset_mems_cookie));

	return NULL;
}
