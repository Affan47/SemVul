u132_init(struct u132 *u132)
{
	int retval;
	u32 control;
	u132_disable(u132);
	u132->next_statechange = jiffies;
	retval = u132_write_pcimem(u132, intrdisable, OHCI_INTR_MIE);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
	if (u132->num_ports == 0) {
		u32 rh_a = -1;
		retval = u132_read_pcimem(u132, roothub.a, &rh_a);
		if (retval)
			return retval;
		u132->num_ports = rh_a & RH_A_NDP;
		retval = read_roothub_info(u132);
		if (retval)
			return retval;
	}
	if (u132->num_ports > MAX_U132_PORTS)
		return -EINVAL;

	return 0;
}
