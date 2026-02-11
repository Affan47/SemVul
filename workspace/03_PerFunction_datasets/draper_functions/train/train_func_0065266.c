hciops_read_clock(int index, bdaddr_t *bdaddr, int which,
						int timeout, uint32_t *clock,
						uint16_t *accuracy)
{
	struct dev_info *dev = &devs[index];
	uint16_t handle = 0;
	char addr[18];
	int ret;

	ba2str(bdaddr, addr);
	DBG("hci%d addr %s which %d timeout %d", index, addr, which, timeout);

	ret = get_handle(index, bdaddr, &handle);
	if (ret < 0)
		return ret;

	if (hci_read_clock(dev->sk, htobs(handle), which, clock, accuracy,
								timeout) < 0)
		return -errno;

	return 0;
}
