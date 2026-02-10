setup_idle_tx_channel (hrz_dev * dev, hrz_vcc * vcc) {
  unsigned short idle_channels;
  short tx_channel = -1;
  unsigned int spin_count;
  PRINTD (DBG_FLOW|DBG_TX, "setup_idle_tx_channel %p", dev);


  spin_count = 0;
  while (!(idle_channels = rd_regw (dev, TX_STATUS_OFF) & IDLE_CHANNELS_MASK)) {
    PRINTD (DBG_TX|DBG_WARN, "waiting for idle TX channel");

    if (++spin_count > 100) {
      PRINTD (DBG_TX|DBG_ERR, "spun out waiting for idle TX channel");
      return -EBUSY;
    }
  }


  {

    int chan = dev->tx_idle;

    int keep_going = 1;
    while (keep_going) {
      if (idle_channels & (1<<chan)) {
	tx_channel = chan;
	keep_going = 0;
      }
      ++chan;
      if (chan == TX_CHANS)
	chan = 0;
    }

    dev->tx_idle = chan;
  }


  {


    tx_ch_desc * tx_desc = &memmap->tx_descs[tx_channel];
    u32 rd_ptr;
    u32 wr_ptr;
    u16 channel = vcc->channel;

    unsigned long flags;
    spin_lock_irqsave (&dev->mem_lock, flags);


    dev->tx_channel_record[tx_channel] = channel;


    update_tx_channel_config (dev, tx_channel, RATE_TYPE_ACCESS,
			      vcc->tx_xbr_bits);


    update_tx_channel_config (dev, tx_channel, PCR_TIMER_ACCESS,
			      vcc->tx_pcr_bits);

#if 0
    if (vcc->tx_xbr_bits == VBR_RATE_TYPE) {

      update_tx_channel_config (dev, tx_channel, SCR_TIMER_ACCESS,
				vcc->tx_scr_bits);


      update_tx_channel_config (dev, tx_channel, BUCKET_CAPACITY_ACCESS,
				vcc->tx_bucket_bits);


      update_tx_channel_config (dev, tx_channel, BUCKET_FULLNESS_ACCESS,
				vcc->tx_bucket_bits);
    }
#endif


    rd_ptr = rd_mem (dev, &tx_desc->rd_buf_type) & BUFFER_PTR_MASK;
    wr_ptr = rd_mem (dev, &tx_desc->wr_buf_type) & BUFFER_PTR_MASK;


    if (rd_ptr != wr_ptr) {
      PRINTD (DBG_TX|DBG_ERR, "TX buffer pointers are broken!");


    }
    PRINTD (DBG_TX, "TX buffer pointers are: rd %x, wr %x.",
	    rd_ptr, wr_ptr);

    switch (vcc->aal) {
      case aal0:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal0");
	rd_ptr |= CHANNEL_TYPE_RAW_CELLS;
	wr_ptr |= CHANNEL_TYPE_RAW_CELLS;
	break;
      case aal34:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal34");
	rd_ptr |= CHANNEL_TYPE_AAL3_4;
	wr_ptr |= CHANNEL_TYPE_AAL3_4;
	break;
      case aal5:
	rd_ptr |= CHANNEL_TYPE_AAL5;
	wr_ptr |= CHANNEL_TYPE_AAL5;

	wr_mem (dev, &tx_desc->partial_crc, INITIAL_CRC);
	break;
    }

    wr_mem (dev, &tx_desc->rd_buf_type, rd_ptr);
    wr_mem (dev, &tx_desc->wr_buf_type, wr_ptr);


    wr_mem (dev, &tx_desc->cell_header, channel);

    spin_unlock_irqrestore (&dev->mem_lock, flags);
  }

  return tx_channel;
}
