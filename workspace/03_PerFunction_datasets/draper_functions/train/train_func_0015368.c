ti_write_byte(struct usb_serial_port *port,
			struct ti_device *tdev, unsigned long addr,
			__u8 mask, __u8 byte)
{
	int status;
	unsigned int size;
	struct ti_write_data_bytes *data;

	dev_dbg(&port->dev, "%s - addr 0x%08lX, mask 0x%02X, byte 0x%02X\n", __func__,
		addr, mask, byte);

	size = sizeof(struct ti_write_data_bytes) + 2;
	data = kmalloc(size, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->bAddrType = TI_RW_DATA_ADDR_XDATA;
	data->bDataType = TI_RW_DATA_BYTE;
	data->bDataCounter = 1;
	data->wBaseAddrHi = cpu_to_be16(addr>>16);
	data->wBaseAddrLo = cpu_to_be16(addr);
	data->bData[0] = mask;
	data->bData[1] = byte;

	status = ti_command_out_sync(tdev, TI_WRITE_DATA, TI_RAM_PORT, 0,
		(__u8 *)data, size);

	if (status < 0)
		dev_err(&port->dev, "%s - failed, %d\n", __func__, status);

	kfree(data);

	return status;
}
