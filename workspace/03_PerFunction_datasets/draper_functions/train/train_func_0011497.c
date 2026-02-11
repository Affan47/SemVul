mos7840_calc_baud_rate_divisor(struct usb_serial_port *port,
					  int baudRate, int *divisor,
					  __u16 *clk_sel_val)
{
	dev_dbg(&port->dev, "%s - %d\n", __func__, baudRate);

	if (baudRate <= 115200) {
		*divisor = 115200 / baudRate;
		*clk_sel_val = 0x0;
	}
	if ((baudRate > 115200) && (baudRate <= 230400)) {
		*divisor = 230400 / baudRate;
		*clk_sel_val = 0x10;
	} else if ((baudRate > 230400) && (baudRate <= 403200)) {
		*divisor = 403200 / baudRate;
		*clk_sel_val = 0x20;
	} else if ((baudRate > 403200) && (baudRate <= 460800)) {
		*divisor = 460800 / baudRate;
		*clk_sel_val = 0x30;
	} else if ((baudRate > 460800) && (baudRate <= 806400)) {
		*divisor = 806400 / baudRate;
		*clk_sel_val = 0x40;
	} else if ((baudRate > 806400) && (baudRate <= 921600)) {
		*divisor = 921600 / baudRate;
		*clk_sel_val = 0x50;
	} else if ((baudRate > 921600) && (baudRate <= 1572864)) {
		*divisor = 1572864 / baudRate;
		*clk_sel_val = 0x60;
	} else if ((baudRate > 1572864) && (baudRate <= 3145728)) {
		*divisor = 3145728 / baudRate;
		*clk_sel_val = 0x70;
	}
	return 0;
}
