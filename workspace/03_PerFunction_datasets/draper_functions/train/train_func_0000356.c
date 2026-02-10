ath3k_init(int fd, int speed, int init_speed, char *bdaddr,
						struct termios *ti)
{
	int r;
	int err = 0;
	struct timespec tm = { 0, 500000 };
	unsigned char cmd[MAX_CMD_LEN], rsp[HCI_MAX_EVENT_SIZE];
	unsigned char *ptr = cmd + 1;
	hci_command_hdr *ch = (void *)ptr;

	cmd[0] = HCI_COMMAND_PKT;


	err = set_cntrlr_baud(fd, speed);
	if (err < 0)
		return err;

	err = set_speed(fd, ti, speed);
	if (err < 0) {
		perror("Can't set required baud rate");
		return err;
	}


	r = ath_ps_download(fd);
	if (r < 0) {
		perror("Failed to Download configuration");
		err = -ETIMEDOUT;
		goto failed;
	}


	if (bdaddr) {
		ch->opcode = htobs(cmd_opcode_pack(HCI_VENDOR_CMD_OGF,
							HCI_PS_CMD_OCF));
		ch->plen = 10;
		ptr += HCI_COMMAND_HDR_SIZE;

		ptr[0] = 0x01;
		ptr[1] = 0x01;
		ptr[2] = 0x00;
		ptr[3] = 0x06;
		str2ba(bdaddr, (bdaddr_t *)(ptr + 4));

		if (write(fd, cmd, WRITE_BDADDR_CMD_LEN) !=
					WRITE_BDADDR_CMD_LEN) {
			perror("Failed to write BD_ADDR command\n");
			err = -ETIMEDOUT;
			goto failed;
		}

		if (read_hci_event(fd, rsp, sizeof(rsp)) < 0) {
			perror("Failed to set BD_ADDR\n");
			err = -ETIMEDOUT;
			goto failed;
		}
	}


	cmd[1] = 0x03;
	cmd[2] = 0x0C;
	cmd[3] = 0x00;

	r = write(fd, cmd, 4);
	if (r != 4) {
		err = -ETIMEDOUT;
		goto failed;
	}

	nanosleep(&tm, NULL);
	if (read_hci_event(fd, rsp, sizeof(rsp)) < 0) {
		err = -ETIMEDOUT;
		goto failed;
	}

	err = set_cntrlr_baud(fd, speed);
	if (err < 0)
		return err;

failed:
	if (err < 0) {
		set_cntrlr_baud(fd, init_speed);
		set_speed(fd, ti, init_speed);
	}

	return err;
}
