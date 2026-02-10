reset(unsigned type)
{
  Bit32u i;

  BX_FD_THIS s.pending_irq = 0;
  BX_FD_THIS s.reset_sensei = 0;

  BX_FD_THIS s.main_status_reg = 0;
  BX_FD_THIS s.status_reg0 = 0;
  BX_FD_THIS s.status_reg1 = 0;
  BX_FD_THIS s.status_reg2 = 0;
  BX_FD_THIS s.status_reg3 = 0;


  if (type == BX_RESET_HARDWARE) {
    BX_FD_THIS s.DOR = 0x0c;


    for (i=0; i<4; i++) {
      BX_FD_THIS s.DIR[i] |= 0x80;
      }
    BX_FD_THIS s.data_rate = 2;
    BX_FD_THIS s.lock = 0;
  } else {
    BX_INFO(("controller reset in software"));
  }
  if (BX_FD_THIS s.lock == 0) {
    BX_FD_THIS s.config = 0;
    BX_FD_THIS s.pretrk = 0;
  }
  BX_FD_THIS s.perp_mode = 0;

  for (i=0; i<4; i++) {
    BX_FD_THIS s.cylinder[i] = 0;
    BX_FD_THIS s.head[i] = 0;
    BX_FD_THIS s.sector[i] = 0;
    BX_FD_THIS s.eot[i] = 0;
  }

  DEV_pic_lower_irq(6);
  if (!(BX_FD_THIS s.main_status_reg & FD_MS_NDMA)) {
    DEV_dma_set_drq(FLOPPY_DMA_CHAN, 0);
  }
  enter_idle_phase();
}
