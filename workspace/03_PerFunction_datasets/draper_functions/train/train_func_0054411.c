calibrate_xor_blocks(void)
{
	void *b1, *b2;
	struct xor_block_template *f, *fastest;


	b1 = (void *) __get_free_pages(GFP_KERNEL | __GFP_NOTRACK, 2);
	if (!b1) {
		printk(KERN_WARNING "xor: Yikes!  No memory available.\n");
		return -ENOMEM;
	}
	b2 = b1 + 2*PAGE_SIZE + BENCH_SIZE;


	fastest = NULL;

#ifdef XOR_SELECT_TEMPLATE
		fastest = XOR_SELECT_TEMPLATE(fastest);
#endif

#define xor_speed(templ)	do_xor_speed((templ), b1, b2)

	if (fastest) {
		printk(KERN_INFO "xor: automatically using best "
				 "checksumming function:\n");
		xor_speed(fastest);
		goto out;
	} else {
		printk(KERN_INFO "xor: measuring software checksum speed\n");
		XOR_TRY_TEMPLATES;
		fastest = template_list;
		for (f = fastest; f; f = f->next)
			if (f->speed > fastest->speed)
				fastest = f;
	}

	printk(KERN_INFO "xor: using function: %s (%d.%03d MB/sec)\n",
	       fastest->name, fastest->speed / 1000, fastest->speed % 1000);

#undef xor_speed

 out:
	free_pages((unsigned long)b1, 2);

	active_template = fastest;
	return 0;
}
