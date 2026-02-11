__replace_page(struct vm_area_struct *vma, unsigned long addr,
				struct page *page, struct page *kpage)
{
	struct mm_struct *mm = vma->vm_mm;
	spinlock_t *ptl;
	pte_t *ptep;
	int err;

	const unsigned long mmun_start = addr;
	const unsigned long mmun_end   = addr + PAGE_SIZE;
	struct mem_cgroup *memcg;

	err = mem_cgroup_try_charge(kpage, vma->vm_mm, GFP_KERNEL, &memcg);
	if (err)
		return err;


	lock_page(page);

	mmu_notifier_invalidate_range_start(mm, mmun_start, mmun_end);
	err = -EAGAIN;
	ptep = page_check_address(page, mm, addr, &ptl, 0);
	if (!ptep) {
		mem_cgroup_cancel_charge(kpage, memcg);
		goto unlock;
	}

	get_page(kpage);
	page_add_new_anon_rmap(kpage, vma, addr);
	mem_cgroup_commit_charge(kpage, memcg, false);
	lru_cache_add_active_or_unevictable(kpage, vma);

	if (!PageAnon(page)) {
		dec_mm_counter(mm, MM_FILEPAGES);
		inc_mm_counter(mm, MM_ANONPAGES);
	}

	flush_cache_page(vma, addr, pte_pfn(*ptep));
	ptep_clear_flush_notify(vma, addr, ptep);
	set_pte_at_notify(mm, addr, ptep, mk_pte(kpage, vma->vm_page_prot));

	page_remove_rmap(page);
	if (!page_mapped(page))
		try_to_free_swap(page);
	pte_unmap_unlock(ptep, ptl);

	if (vma->vm_flags & VM_LOCKED)
		munlock_vma_page(page);
	put_page(page);

	err = 0;
 unlock:
	mmu_notifier_invalidate_range_end(mm, mmun_start, mmun_end);
	unlock_page(page);
	return err;
}
