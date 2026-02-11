scif_destroy_window(struct scif_endpt *ep, struct scif_window *window)
{
	int j;
	struct scif_pinned_pages *pinned_pages = window->pinned_pages;
	int nr_pages = window->nr_pages;

	might_sleep();
	if (!window->temp && window->mm) {
		__scif_dec_pinned_vm_lock(window->mm, window->nr_pages, 0);
		__scif_release_mm(window->mm);
		window->mm = NULL;
	}

	scif_free_window_offset(ep, window, window->offset);
	scif_unmap_window(ep->remote_dev, window);


	j = atomic_sub_return(1, &pinned_pages->ref_count);
	if (j < 0)
		dev_err(scif_info.mdev.this_device,
			"%s %d incorrect ref count %d\n",
			__func__, __LINE__, j);


	if (!j)
		scif_destroy_pinned_pages(window->pinned_pages);
	scif_free(window->dma_addr, nr_pages * sizeof(*window->dma_addr));
	scif_free(window->num_pages, nr_pages * sizeof(*window->num_pages));
	window->magic = 0;
	scif_free(window, sizeof(*window));
	return 0;
}
