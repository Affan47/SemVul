__get_page_tail(struct page *page)
{


	unsigned long flags;
	bool got;
	struct page *page_head = compound_head(page);


	if (!__compound_tail_refcounted(page_head)) {
		smp_rmb();
		if (likely(PageTail(page))) {


			VM_BUG_ON_PAGE(!PageHead(page_head), page_head);
			__get_page_tail_foll(page, true);
			return true;
		} else {


			return false;
		}
	}

	got = false;
	if (likely(page != page_head && get_page_unless_zero(page_head))) {


		flags = compound_lock_irqsave(page_head);

		if (likely(PageTail(page))) {
			__get_page_tail_foll(page, false);
			got = true;
		}
		compound_unlock_irqrestore(page_head, flags);
		if (unlikely(!got))
			put_page(page_head);
	}
	return got;
}
