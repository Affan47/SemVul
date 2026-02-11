avc_bridgeco_get_plug_type(struct fw_unit *unit,
			       u8 addr[AVC_BRIDGECO_ADDR_BYTES],
			       enum avc_bridgeco_plug_type *type)
{
	u8 *buf;
	int err;

	buf = kzalloc(12, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;


	avc_bridgeco_fill_plug_info_extension_command(buf, addr, 0x00);

	err = fcp_avc_transaction(unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(9));
	if ((err >= 0) && (err < 8))
		err = -EIO;
	else if (buf[0] == 0x08)
		err = -ENOSYS;
	else if (buf[0] == 0x0a)
		err = -EINVAL;
	else if (buf[0] == 0x0b)
		err = -EAGAIN;
	if (err < 0)
		goto end;

	*type = buf[10];
	err = 0;
end:
	kfree(buf);
	return err;
}
