cfag12864b_init(void)
{
	int ret = -EINVAL;


	if (!ks0108_isinited()) {
		printk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"ks0108 is not initialized\n");
		goto none;
	}
	BUILD_BUG_ON(PAGE_SIZE < CFAG12864B_SIZE);

	cfag12864b_buffer = (unsigned char *) get_zeroed_page(GFP_KERNEL);
	if (cfag12864b_buffer == NULL) {
		printk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"can't get a free page\n");
		ret = -ENOMEM;
		goto none;
	}

	cfag12864b_cache = kmalloc(sizeof(unsigned char) *
		CFAG12864B_SIZE, GFP_KERNEL);
	if (cfag12864b_cache == NULL) {
		printk(KERN_ERR CFAG12864B_NAME ": ERROR: "
			"can't alloc cache buffer (%i bytes)\n",
			CFAG12864B_SIZE);
		ret = -ENOMEM;
		goto bufferalloced;
	}

	cfag12864b_workqueue = create_singlethread_workqueue(CFAG12864B_NAME);
	if (cfag12864b_workqueue == NULL)
		goto cachealloced;

	cfag12864b_clear();
	cfag12864b_on();

	cfag12864b_inited = 1;
	return 0;

cachealloced:
	kfree(cfag12864b_cache);

bufferalloced:
	free_page((unsigned long) cfag12864b_buffer);

none:
	return ret;
}
