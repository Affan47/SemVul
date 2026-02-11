vmxnet3_get_hw_addr ( struct vmxnet3_nic *vmxnet, void *hw_addr ) {
	struct {
		uint32_t low;
		uint32_t high;
	} __attribute__ (( packed )) mac;

	mac.low = le32_to_cpu ( vmxnet3_command ( vmxnet,
					       VMXNET3_CMD_GET_PERM_MAC_LO ) );
	mac.high = le32_to_cpu ( vmxnet3_command ( vmxnet,
					       VMXNET3_CMD_GET_PERM_MAC_HI ) );
	memcpy ( hw_addr, &mac, ETH_ALEN );
}
