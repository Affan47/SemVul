EnableSRAM(THINKPAD_BD_DATA * pBDData)
{
	DSP_3780I_CONFIG_SETTINGS *pSettings = &pBDData->rDspSettings;
	unsigned short usDspBaseIO = pSettings->usDspBaseIO;
	DSP_GPIO_OUTPUT_DATA_15_8 rGpioOutputData;
	DSP_GPIO_DRIVER_ENABLE_15_8 rGpioDriverEnable;
	DSP_GPIO_MODE_15_8 rGpioMode;

	PRINTK_1(TRACE_TP3780I, "tp3780i::EnableSRAM, entry\n");

	MKWORD(rGpioMode) = ReadMsaCfg(DSP_GpioModeControl_15_8);
	rGpioMode.GpioMode10 = 0;
	WriteMsaCfg(DSP_GpioModeControl_15_8, MKWORD(rGpioMode));

	MKWORD(rGpioDriverEnable) = 0;
	rGpioDriverEnable.Enable10 = TRUE;
	rGpioDriverEnable.Mask10 = TRUE;
	WriteMsaCfg(DSP_GpioDriverEnable_15_8, MKWORD(rGpioDriverEnable));

	MKWORD(rGpioOutputData) = 0;
	rGpioOutputData.Latch10 = 0;
	rGpioOutputData.Mask10 = TRUE;
	WriteMsaCfg(DSP_GpioOutputData_15_8, MKWORD(rGpioOutputData));

	PRINTK_1(TRACE_TP3780I, "tp3780i::EnableSRAM exit\n");
}
