hrz_open_rx (hrz_dev * dev, u16 channel) {


  unsigned long flags;
  u32 channel_type;

  u16 buf_ptr = RX_CHANNEL_IDLE;

  rx_ch_desc * rx_desc = &memmap->rx_descs[channel];

  PRINTD (DBG_FLOW, "hrz_open_rx %x", channel);

  spin_lock_irqsave (&dev->mem_lock, flags);
  channel_type = rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK;
  spin_unlock_irqrestore (&dev->mem_lock, flags);


  if (channel_type != RX_CHANNEL_DISABLED) {
    PRINTD (DBG_ERR|DBG_VCC, "RX channel for VC already open");
    return -EBUSY;
  }


  if (dev->noof_spare_buffers) {
    buf_ptr = dev->spare_buffers[--dev->noof_spare_buffers];
    PRINTD (DBG_VCC, "using a spare buffer: %u", buf_ptr);

    if (buf_ptr == RX_CHANNEL_DISABLED || buf_ptr == RX_CHANNEL_IDLE) {

      PRINTD (DBG_ERR|DBG_VCC, "bad spare buffer pointer, using IDLE");
      buf_ptr = RX_CHANNEL_IDLE;
    }
  } else {
    PRINTD (DBG_VCC, "using IDLE buffer pointer");
  }


  spin_lock_irqsave (&dev->mem_lock, flags);

  wr_mem (dev, &rx_desc->wr_buf_type,
	  buf_ptr | CHANNEL_TYPE_AAL5 | FIRST_CELL_OF_AAL5_FRAME);
  if (buf_ptr != RX_CHANNEL_IDLE)
    wr_mem (dev, &rx_desc->rd_buf_type, buf_ptr);

  spin_unlock_irqrestore (&dev->mem_lock, flags);


  PRINTD (DBG_FLOW, "hrz_open_rx ok");

  return 0;
}
