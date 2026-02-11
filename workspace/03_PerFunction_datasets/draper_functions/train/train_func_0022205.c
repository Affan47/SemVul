pps_poweroff_atca(ipmi_user_t user)
{
	struct ipmi_system_interface_addr smi_addr;
	struct kernel_ipmi_msg            send_msg;
	int                               rv;


	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	printk(KERN_INFO PFX "PPS powerdown hook used");

	send_msg.netfn = IPMI_NETFN_OEM;
	send_msg.cmd = IPMI_ATCA_PPS_GRACEFUL_RESTART;
	send_msg.data = IPMI_ATCA_PPS_IANA;
	send_msg.data_len = 3;
	rv = ipmi_request_in_rc_mode(user,
				     (struct ipmi_addr *) &smi_addr,
				     &send_msg);
	if (rv && rv != IPMI_UNKNOWN_ERR_COMPLETION_CODE) {
		printk(KERN_ERR PFX "Unable to send ATCA ,"
		       " IPMI error 0x%x\n", rv);
	}
	return;
}
