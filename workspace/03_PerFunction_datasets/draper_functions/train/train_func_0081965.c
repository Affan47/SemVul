mptfc_dump_lun_info(MPT_ADAPTER *ioc, struct fc_rport *rport, struct scsi_device *sdev,
		VirtTarget *vtarget)
{
	u64 nn, pn;
	struct mptfc_rport_info *ri;

	ri = *((struct mptfc_rport_info **)rport->dd_data);
	pn = (u64)ri->pg0.WWPN.High << 32 | (u64)ri->pg0.WWPN.Low;
	nn = (u64)ri->pg0.WWNN.High << 32 | (u64)ri->pg0.WWNN.Low;
	dfcprintk (ioc, printk(MYIOC_s_DEBUG_FMT
		"mptfc_slv_alloc.%d: num_luns %d, sdev.id %d, "
		"CurrentTargetID %d, %x %llx %llx\n",
		ioc->name,
		sdev->host->host_no,
		vtarget->num_luns,
		sdev->id, ri->pg0.CurrentTargetID,
		ri->pg0.PortIdentifier,
		(unsigned long long)pn,
		(unsigned long long)nn));
}
