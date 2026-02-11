__split_huge_page(struct page *page,
			      struct anon_vma *anon_vma,
			      struct list_head *list)
{
	int mapcount, mapcount2;
	pgoff_t pgoff = page->index << (PAGE_CACHE_SHIFT - PAGE_SHIFT);
	struct anon_vma_chain *avc;

	BUG_ON(!PageHead(page));
	BUG_ON(PageTail(page));

	mapcount = 0;
	anon_vma_interval_tree_foreach(avc, &anon_vma->rb_root, pgoff, pgoff) {
		struct vm_area_struct *vma = avc->vma;
		unsigned long addr = vma_address(page, vma);
		BUG_ON(is_vma_temporary_stack(vma));
		mapcount += __split_huge_page_splitting(page, vma, addr);
	}


	if (mapcount != page_mapcount(page)) {
		pr_err("mapcount %d page_mapcount %d\n",
			mapcount, page_mapcount(page));
		BUG();
	}

	__split_huge_page_refcount(page, list);

	mapcount2 = 0;
	anon_vma_interval_tree_foreach(avc, &anon_vma->rb_root, pgoff, pgoff) {
		struct vm_area_struct *vma = avc->vma;
		unsigned long addr = vma_address(page, vma);
		BUG_ON(is_vma_temporary_stack(vma));
		mapcount2 += __split_huge_page_map(page, vma, addr);
	}
	if (mapcount != mapcount2) {
		pr_err("mapcount %d mapcount2 %d page_mapcount %d\n",
			mapcount, mapcount2, page_mapcount(page));
		BUG();
	}
}
