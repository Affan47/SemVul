av7110_detach(struct saa7146_dev* saa)
{
	struct av7110 *av7110 = saa->ext_priv;
	dprintk(4, "%p\n", av7110);

#if IS_ENABLED(CONFIG_DVB_AV7110_IR)
	av7110_ir_exit(av7110);
#endif
	if (budgetpatch || av7110->full_ts) {
		if (budgetpatch) {

			saa7146_write(saa, MC1, MASK_29);

			saa7146_setgpio(saa, 3, SAA7146_GPIO_OUTLO);
		}
		saa7146_write(saa, MC1, MASK_20);
		SAA7146_IER_DISABLE(saa, MASK_10);
		SAA7146_ISR_CLEAR(saa, MASK_10);
		msleep(50);
		tasklet_kill(&av7110->vpe_tasklet);
		saa7146_vfree_destroy_pgtable(saa->pci, av7110->grabbing, &av7110->pt);
	}
	av7110_exit_v4l(av7110);

	av7110_arm_sync(av7110);

	tasklet_kill(&av7110->debi_tasklet);
	tasklet_kill(&av7110->gpio_tasklet);

	dvb_unregister(av7110);

	SAA7146_IER_DISABLE(saa, MASK_19 | MASK_03);
	SAA7146_ISR_CLEAR(saa, MASK_19 | MASK_03);

	av7110_ca_exit(av7110);
	av7110_av_exit(av7110);

	vfree(av7110->iobuf);
	pci_free_consistent(saa->pci, 8192, av7110->debi_virt,
			    av7110->debi_bus);

	i2c_del_adapter(&av7110->i2c_adap);

	dvb_unregister_adapter (&av7110->dvb_adapter);

	av7110_num--;

	put_firmware(av7110);

	kfree(av7110);

	saa->ext_priv = NULL;

	return 0;
}
