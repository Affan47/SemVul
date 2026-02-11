usb6fire_control_set_channels(
	struct control_runtime *rt, int n_analog_out,
	int n_analog_in, bool spdif_out, bool spdif_in)
{
	int ret;
	struct comm_runtime *comm_rt = rt->chip->comm;


	ret = comm_rt->write16(comm_rt, 0x02, 0x02,
			(1 << (n_analog_out / 2)) - 1,
			(1 << (n_analog_in / 2)) - 1);
	if (ret < 0)
		return ret;


	ret = comm_rt->write16(comm_rt, 0x02, 0x03, 0x00, 0x00);
	if (ret < 0)
		return ret;

	return 0;
}
