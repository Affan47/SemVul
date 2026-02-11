_fw_usb_suspend_reboot()
{

	_fw_reset_dma_fifo();


	_fw_restore_dma_fifo();


	iowrite32(MAGPIE_REG_CPU_PLL_BYPASS_ADDR, BIT0 | BIT4);

	A_DELAY_USECS(100);

	iowrite32(MAGPIE_REG_CPU_PLL_ADDR, BIT16);

	A_DELAY_USECS(100);
	A_UART_HWINIT((40*1000*1000), 19200);

	A_CLOCK_INIT(40);

	if (!bEepromExist) {
		bJumptoFlash = TRUE;
		A_PRINTF("Jump to Flash BOOT\n");
		app_start();
	} else {
		A_PRINTF("receive the suspend command...\n");

		A_USB_JUMP_BOOT();
	}

}
