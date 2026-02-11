bm_page_lock_io(struct drbd_device *device, int page_nr)
{
	struct drbd_bitmap *b = device->bitmap;
	void *addr = &page_private(b->bm_pages[page_nr]);
	wait_event(b->bm_io_wait, !test_and_set_bit(BM_PAGE_IO_LOCK, addr));
}
