alsa_sound_init(void)
{
	snd_major = major;
	snd_ecards_limit = cards_limit;
	if (register_chrdev(major, "alsa", &snd_fops)) {
		pr_err("ALSA core: unable to register native major device number %d\n", major);
		return -EIO;
	}
	if (snd_info_init() < 0) {
		unregister_chrdev(major, "alsa");
		return -ENOMEM;
	}
#ifndef MODULE
	pr_info("Advanced Linux Sound Architecture Driver Initialized.\n");
#endif
	return 0;
}
