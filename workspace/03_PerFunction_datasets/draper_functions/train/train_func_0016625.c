sirdev_tx_complete_fsm(struct sir_dev *dev)
{
	struct sir_fsm *fsm = &dev->fsm;
	unsigned next_state, delay;
	unsigned bytes_left;

	do {
		next_state = fsm->substate;
		delay = 0;

		switch(fsm->substate) {

		case SIRDEV_STATE_WAIT_XMIT:
			if (dev->drv->chars_in_buffer)
				bytes_left = dev->drv->chars_in_buffer(dev);
			else
				bytes_left = 0;
			if (!bytes_left) {
				next_state = SIRDEV_STATE_WAIT_UNTIL_SENT;
				break;
			}

			if (dev->speed > 115200)
				delay = (bytes_left*8*10000) / (dev->speed/100);
			else if (dev->speed > 0)
				delay = (bytes_left*10*10000) / (dev->speed/100);
			else
				delay = 0;

			if (delay < 100) {
				udelay(delay);
				delay = 0;
				break;
			}

			delay = (delay+999) / 1000;
			break;

		case SIRDEV_STATE_WAIT_UNTIL_SENT:

			if (dev->drv->wait_until_sent)
				dev->drv->wait_until_sent(dev);
			next_state = SIRDEV_STATE_TX_DONE;
			break;

		case SIRDEV_STATE_TX_DONE:
			return 0;

		default:
			net_err_ratelimited("%s - undefined state\n", __func__);
			return -EINVAL;
		}
		fsm->substate = next_state;
	} while (delay == 0);
	return delay;
}
