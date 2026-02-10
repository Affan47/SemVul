pm3393_interrupt_handler(struct cmac *cmac)
{
	u32 master_intr_status;


	pmread(cmac, SUNI1x10GEXP_REG_MASTER_INTERRUPT_STATUS,
	       &master_intr_status);
	if (netif_msg_intr(cmac->adapter))
		dev_dbg(&cmac->adapter->pdev->dev, "PM3393 intr cause 0x%x\n",
			master_intr_status);


	pm3393_interrupt_clear(cmac);

	return 0;
}
