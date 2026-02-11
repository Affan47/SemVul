save_image(struct swap_map_handle *handle,
                      struct snapshot_handle *snapshot,
                      unsigned int nr_to_write)
{
	unsigned int m;
	int ret;
	int nr_pages;
	int err2;
	struct hib_bio_batch hb;
	ktime_t start;
	ktime_t stop;

	hib_init_batch(&hb);

	printk(KERN_INFO "PM: Saving image data pages (%u pages)...\n",
		nr_to_write);
	m = nr_to_write / 10;
	if (!m)
		m = 1;
	nr_pages = 0;
	start = ktime_get();
	while (1) {
		ret = snapshot_read_next(snapshot);
		if (ret <= 0)
			break;
		ret = swap_write_page(handle, data_of(*snapshot), &hb);
		if (ret)
			break;
		if (!(nr_pages % m))
			printk(KERN_INFO "PM: Image saving progress: %3d%%\n",
			       nr_pages / m * 10);
		nr_pages++;
	}
	err2 = hib_wait_io(&hb);
	stop = ktime_get();
	if (!ret)
		ret = err2;
	if (!ret)
		printk(KERN_INFO "PM: Image saving done.\n");
	swsusp_show_speed(start, stop, nr_to_write, "Wrote");
	return ret;
}
