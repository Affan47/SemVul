ahc_alloc(void *platform_arg, char *name)
{
	struct  ahc_softc *ahc;
	int	i;

#ifndef	__FreeBSD__
	ahc = kmalloc(sizeof(*ahc), GFP_ATOMIC);
	if (!ahc) {
		printk("aic7xxx: cannot malloc softc!\n");
		kfree(name);
		return NULL;
	}
#else
	ahc = device_get_softc((device_t)platform_arg);
#endif
	memset(ahc, 0, sizeof(*ahc));
	ahc->seep_config = kmalloc(sizeof(*ahc->seep_config), GFP_ATOMIC);
	if (ahc->seep_config == NULL) {
#ifndef	__FreeBSD__
		kfree(ahc);
#endif
		kfree(name);
		return (NULL);
	}
	LIST_INIT(&ahc->pending_scbs);

	ahc->name = name;
	ahc->unit = -1;
	ahc->description = NULL;
	ahc->channel = 'A';
	ahc->channel_b = 'B';
	ahc->chip = AHC_NONE;
	ahc->features = AHC_FENONE;
	ahc->bugs = AHC_BUGNONE;
	ahc->flags = AHC_FNONE;


	ahc->seqctl = FASTMODE;

	for (i = 0; i < AHC_NUM_TARGETS; i++)
		TAILQ_INIT(&ahc->untagged_queues[i]);
	if (ahc_platform_alloc(ahc, platform_arg) != 0) {
		ahc_free(ahc);
		ahc = NULL;
	}
	return (ahc);
}
