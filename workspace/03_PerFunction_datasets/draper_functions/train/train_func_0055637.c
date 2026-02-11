slapi_sdn_copy(const Slapi_DN *from, Slapi_DN *to)
{
	SDN_DUMP( from, "slapi_sdn_copy from");
	SDN_DUMP( to, "slapi_sdn_copy to");
	slapi_sdn_done(to);
	if (from->udn)
	{
		to->flag = slapi_setbit_uchar(to->flag, FLAG_UDN);
		to->udn= slapi_ch_strdup(from->udn);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_udn_created);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_udn_exist);
	}
	if (from->dn)
	{
		to->flag = slapi_setbit_uchar(to->flag, FLAG_DN);
		to->dn = slapi_ch_strdup(from->dn);

		to->ndn_len = strlen(to->dn);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_dn_created);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_dn_exist);
	}
	if (from->ndn)
	{
		to->flag = slapi_setbit_uchar(to->flag, FLAG_NDN);
		to->ndn = slapi_ch_strdup(from->ndn);
		to->ndn_len = strlen(to->ndn);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_ndn_created);
		PR_INCREMENT_COUNTER(slapi_sdn_counter_ndn_exist);
	}
}
