end_swap_bio_write(struct bio *bio)
{
	struct page *page = bio->bi_io_vec[0].bv_page;

	if (bio->bi_error) {
		SetPageError(page);


		set_page_dirty(page);
		printk(KERN_ALERT "Write-error on swap-device (%u:%u:%Lu)\n",
				imajor(bio->bi_bdev->bd_inode),
				iminor(bio->bi_bdev->bd_inode),
				(unsigned long long)bio->bi_iter.bi_sector);
		ClearPageReclaim(page);
	}
	end_page_writeback(page);
	bio_put(bio);
}
