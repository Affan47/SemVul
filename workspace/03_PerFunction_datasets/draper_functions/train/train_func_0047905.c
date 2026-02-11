_transport_get_linkerrors(struct sas_phy *phy)
{
	struct MPT3SAS_ADAPTER *ioc = phy_to_ioc(phy);
	unsigned long flags;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasPhyPage1_t phy_pg1;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	if (_transport_sas_node_find_by_sas_address(ioc,
	    phy->identify.sas_address) == NULL) {
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		return -EINVAL;
	}
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	if (phy->identify.sas_address != ioc->sas_hba.sas_address)
		return _transport_get_expander_phy_error_log(ioc, phy);


	if ((mpt3sas_config_get_phy_pg1(ioc, &mpi_reply, &phy_pg1,
		    phy->number))) {
		pr_err(MPT3SAS_FMT "failure at %s:%d/%s()!\n",
		    ioc->name, __FILE__, __LINE__, __func__);
		return -ENXIO;
	}

	if (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo)
		pr_info(MPT3SAS_FMT
			"phy(%d), ioc_status (0x%04x), loginfo(0x%08x)\n",
			ioc->name, phy->number,
			le16_to_cpu(mpi_reply.IOCStatus),
		    le32_to_cpu(mpi_reply.IOCLogInfo));

	phy->invalid_dword_count = le32_to_cpu(phy_pg1.InvalidDwordCount);
	phy->running_disparity_error_count =
	    le32_to_cpu(phy_pg1.RunningDisparityErrorCount);
	phy->loss_of_dword_sync_count =
	    le32_to_cpu(phy_pg1.LossDwordSynchCount);
	phy->phy_reset_problem_count =
	    le32_to_cpu(phy_pg1.PhyResetProblemCount);
	return 0;
}
