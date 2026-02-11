ipmi_atca_detect(ipmi_user_t user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;
	unsigned char                     data[1];


	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;


	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_GET_ADDR_INFO_CMD;
	data[0] = IPMI_PICMG_ID;
	send_msg.data = data;
	send_msg.data_len = sizeof(data);
	rv = ipmi_request_wait_for_response(user,
					    (struct ipmi_addr *) &smi_addr,
					    &send_msg);

	printk(KERN_INFO PFX "ATCA Detect mfg 0x%X prod 0x%X\n",
	       mfg_id, prod_id);
	if ((mfg_id == IPMI_MOTOROLA_MANUFACTURER_ID)
	    && (prod_id == IPMI_MOTOROLA_PPS_IPMC_PRODUCT_ID)) {
		printk(KERN_INFO PFX
		       "Installing Pigeon Point Systems Poweroff Hook\n");
		atca_oem_poweroff_hook = pps_poweroff_atca;
	}
	return !rv;
}
