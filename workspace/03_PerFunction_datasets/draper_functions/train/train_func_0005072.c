rt2800usb_txdone(struct rt2x00_dev *rt2x00dev)
{
	struct data_queue *queue;
	struct queue_entry *entry;
	u32 reg;
	u8 qid;
	enum txdone_entry_desc_flags done_status;

	while (kfifo_get(&rt2x00dev->txstatus_fifo, &reg)) {


		qid = rt2x00_get_field32(reg, TX_STA_FIFO_PID_QUEUE);
		queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);

		if (unlikely(rt2x00queue_empty(queue))) {
			rt2x00_dbg(rt2x00dev, "Got TX status for an empty queue %u, dropping\n",
				   qid);
			break;
		}

		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);

		if (unlikely(test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
			     !test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))) {
			rt2x00_warn(rt2x00dev, "Data pending for entry %u in queue %u\n",
				    entry->entry_idx, qid);
			break;
		}

		done_status = rt2800usb_txdone_entry_check(entry, reg);
		if (likely(done_status == TXDONE_SUCCESS))
			rt2800_txdone_entry(entry, reg, rt2800usb_get_txwi(entry));
		else
			rt2x00lib_txdone_noinfo(entry, done_status);
	}
}
