do_init_aedsp16(void) {
	printk("Audio Excel DSP 16 init driver Copyright (C) Riccardo Facchetti 1995-98\n");
	if (io == -1 || dma == -1 || irq == -1) {
		printk(KERN_INFO "aedsp16: I/O, IRQ and DMA are mandatory\n");
		return -EINVAL;
	}

	ae_config.base_io = io;
	ae_config.irq = irq;
	ae_config.dma = dma;

	ae_config.mss_base = mss_base;
	ae_config.mpu_base = mpu_base;
	ae_config.mpu_irq = mpu_irq;

	if (init_aedsp16() == FALSE) {
		printk(KERN_ERR "aedsp16: initialization failed\n");


		return -EINVAL;
	}
	return 0;
}
