cx23885_sp2_ci_ctrl(void *priv, u8 read, int addr,
				u8 data, int *mem)
{

	#define SP2_DATA              0x000000ff
	#define SP2_WR                0x00008000
	#define SP2_RD                0x00004000
	#define SP2_ACK               0x00001000
	#define SP2_ADHI              0x00000800
	#define SP2_ADLO              0x00000400
	#define SP2_CS1               0x00000200
	#define SP2_CS0               0x00000100
	#define SP2_EN_ALL            0x00001000
	#define SP2_CTRL_OFF          (SP2_CS1 | SP2_CS0 | SP2_WR | SP2_RD)

	struct cx23885_tsport *port = priv;
	struct cx23885_dev *dev = port->dev;
	int ret;
	int tmp = 0;
	unsigned long timeout;

	mutex_lock(&dev->gpio_lock);


	cx_write(MC417_OEN, SP2_EN_ALL);
	cx_write(MC417_RWD, SP2_CTRL_OFF |
				SP2_ADLO | (0xff & addr));
	cx_clear(MC417_RWD, SP2_ADLO);
	cx_write(MC417_RWD, SP2_CTRL_OFF |
				SP2_ADHI | (0xff & (addr >> 8)));
	cx_clear(MC417_RWD, SP2_ADHI);

	if (read)

		cx_write(MC417_OEN, SP2_EN_ALL | SP2_DATA);
	else

		cx_write(MC417_RWD, SP2_CTRL_OFF | data);


	cx_clear(MC417_RWD, SP2_CS0);


	cx_clear(MC417_RWD, (read) ? SP2_RD : SP2_WR);


	timeout = jiffies + msecs_to_jiffies(1);
	while (!time_after(jiffies, timeout)) {
		tmp = cx_read(MC417_RWD);
		if ((tmp & SP2_ACK) == 0)
			break;
		usleep_range(50, 100);
	}

	cx_set(MC417_RWD, SP2_CTRL_OFF);
	*mem = tmp & 0xff;

	mutex_unlock(&dev->gpio_lock);

	if (!read) {
		if (*mem < 0) {
			ret = -EREMOTEIO;
			goto err;
		}
	}

	return 0;
err:
	return ret;
}
