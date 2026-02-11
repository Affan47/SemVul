set_ext_port_info(ib_portid_t * dest, uint8_t * data, int portnum)
{
	if (!smp_set_via(data, dest, IB_ATTR_MLNX_EXT_PORT_INFO,
			 portnum, 0, srcport))
		IBERROR("smp set ext portinfo failed");

	printf("\nAfter ExtendedPortInfo set:\n");
	show_ext_port_info(dest, data, portnum);
}
