abituguru_write(struct abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, u8 *buf, int count)
{


	int i, timeout = ABIT_UGURU_READY_TIMEOUT;


	i = abituguru_send_address(data, bank_addr, sensor_addr,
		ABIT_UGURU_MAX_RETRIES);
	if (i)
		return i;


	for (i = 0; i < count; i++) {
		if (abituguru_wait(data, ABIT_UGURU_STATUS_WRITE)) {
			ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for "
				"write state (bank: %d, sensor: %d)\n",
				(int)bank_addr, (int)sensor_addr);
			break;
		}
		outb(buf[i], data->addr + ABIT_UGURU_CMD);
	}


	if (abituguru_wait(data, ABIT_UGURU_STATUS_READ)) {
		ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for read state "
			"after write (bank: %d, sensor: %d)\n", (int)bank_addr,
			(int)sensor_addr);
		return -EIO;
	}


	while (inb_p(data->addr + ABIT_UGURU_CMD) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGURU_DEBUG(1, "CMD reg does not hold 0xAC after "
				"write (bank: %d, sensor: %d)\n",
				(int)bank_addr, (int)sensor_addr);
			return -EIO;
		}
		msleep(0);
	}


	abituguru_ready(data);

	return i;
}
