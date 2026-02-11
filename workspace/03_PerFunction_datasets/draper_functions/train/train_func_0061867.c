epic100_poll(struct nic *nic, int retrieve)
{
    int entry;
    int retcode;
    int status;
    entry = cur_rx % RX_RING_SIZE;

    if ((rx_ring[entry].status & cpu_to_le32(RRING_OWN)) == RRING_OWN)
	return (0);

    if ( ! retrieve ) return 1;

    status = le32_to_cpu(rx_ring[entry].status);


#if	(EPIC_DEBUG > 4)
    printf("epic_poll: entry %d status %hX\n", entry, status);
#endif

    cur_rx++;
    if (status & 0x2000) {
	printf("epic_poll: Giant packet\n");
	retcode = 0;
    } else if (status & 0x0006) {

	printf("epic_poll: Frame received with errors\n");
	retcode = 0;
    } else {

	nic->packetlen = le32_to_cpu((rx_ring[entry].buflength))- 4;
	memcpy(nic->packet, &rx_packet[entry * PKT_BUF_SZ], nic->packetlen);
	retcode = 1;
    }


    outl(status & INTR_CLEARERRS, intstat);


    rx_ring[entry].status = RRING_OWN;


    outl(CR_START_RX | CR_QUEUE_RX, command);

    return retcode;
}
