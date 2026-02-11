_transport_sas_node_find_by_sas_address(struct MPT3SAS_ADAPTER *ioc,
	u64 sas_address)
{
	if (ioc->sas_hba.sas_address == sas_address)
		return &ioc->sas_hba;
	else
		return mpt3sas_scsih_expander_find_by_sas_address(ioc,
		    sas_address);
}
