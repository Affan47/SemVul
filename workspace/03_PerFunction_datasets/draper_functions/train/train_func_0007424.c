spc_emulate_evpd_b2(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;


	buf[0] = dev->transport->get_device_type(dev);


	put_unaligned_be16(0x0004, &buf[2]);


	buf[4] = 0x00;


	if (dev->dev_attrib.emulate_tpu != 0)
		buf[5] = 0x80;


	if (dev->dev_attrib.emulate_tpws != 0)
		buf[5] |= 0x40 | 0x20;

	return 0;
}
