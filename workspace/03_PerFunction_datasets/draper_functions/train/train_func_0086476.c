videocodec_init (void)
{
#ifdef CONFIG_PROC_FS
	static struct proc_dir_entry *videocodec_proc_entry;
#endif

	printk(KERN_INFO "Linux video codec intermediate layer: %s\n",
	       VIDEOCODEC_VERSION);

#ifdef CONFIG_PROC_FS
	videocodec_proc_entry = proc_create("videocodecs", 0, NULL, &videocodecs_proc_fops);
	if (!videocodec_proc_entry) {
		dprintk(1, KERN_ERR "videocodec: can't init procfs.\n");
	}
#endif
	return 0;
}
