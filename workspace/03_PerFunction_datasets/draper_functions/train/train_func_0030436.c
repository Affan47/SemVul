sensor_write_8(struct gspca_dev *gspca_dev, u8 addr, u8 data)
{

	reg_w(gspca_dev, STK1135_REG_SBUSW, addr);
	reg_w(gspca_dev, STK1135_REG_SBUSW + 1, data);

	reg_w(gspca_dev, STK1135_REG_SICTL, 0x01);

	if (stk1135_serial_wait_ready(gspca_dev)) {
		pr_err("Sensor write failed\n");
		return;
	}
}
