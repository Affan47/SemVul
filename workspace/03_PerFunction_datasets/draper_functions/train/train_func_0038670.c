mptscsih_event_process(MPT_ADAPTER *ioc, EventNotificationReply_t *pEvReply)
{
	u8 event = le32_to_cpu(pEvReply->Event) & 0xFF;

	devtverboseprintk(ioc, printk(MYIOC_s_DEBUG_FMT
		"MPT event (=%02Xh) routed to SCSI host driver!\n",
		ioc->name, event));

	if ((event == MPI_EVENT_IOC_BUS_RESET ||
	    event == MPI_EVENT_EXT_BUS_RESET) &&
	    (ioc->bus_type == SPI) && (ioc->soft_resets < -1))
			ioc->soft_resets++;

	return 1;
}
