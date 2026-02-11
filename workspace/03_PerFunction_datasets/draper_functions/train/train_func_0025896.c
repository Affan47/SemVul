timer()
{
  Bit8u drive, motor_on;

  drive = BX_FD_THIS s.DOR & 0x03;
  switch (BX_FD_THIS s.pending_command) {
    case 0x07:
      BX_FD_THIS s.status_reg0 = 0x20 | drive;
      motor_on = ((BX_FD_THIS s.DOR>>(drive+4)) & 0x01);
      if ((BX_FD_THIS s.device_type[drive] == FDRIVE_NONE) || (motor_on == 0)) {
        BX_FD_THIS s.status_reg0 |= 0x50;
      }
      enter_idle_phase();
      BX_FD_THIS raise_interrupt();
      break;

    case 0x0f:
      BX_FD_THIS s.status_reg0 = 0x20 | (BX_FD_THIS s.head[drive]<<2) | drive;
      enter_idle_phase();
      BX_FD_THIS raise_interrupt();
      break;

    case 0x4a:
      enter_result_phase();
      break;

    case 0x45:
    case 0xc5:
      if (BX_FD_THIS s.TC) {
        BX_FD_THIS s.status_reg0 = (BX_FD_THIS s.head[drive] << 2) | drive;
        BX_FD_THIS s.status_reg1 = 0;
        BX_FD_THIS s.status_reg2 = 0;

        BX_DEBUG(("<<WRITE DONE>>"));
        BX_DEBUG(("AFTER"));
        BX_DEBUG(("  drive    = %u", drive));
        BX_DEBUG(("  head     = %u", BX_FD_THIS s.head[drive]));
        BX_DEBUG(("  cylinder = %u", BX_FD_THIS s.cylinder[drive]));
        BX_DEBUG(("  sector   = %u", BX_FD_THIS s.sector[drive]));

        enter_result_phase();
      } else {

        if (!(BX_FD_THIS s.main_status_reg & FD_MS_NDMA)) {
          DEV_dma_set_drq(FLOPPY_DMA_CHAN, 1);
        }
      }
      break;

    case 0x46:
    case 0x66:
    case 0xc6:
    case 0xe6:

      if (BX_FD_THIS s.main_status_reg & FD_MS_NDMA) {
        BX_FD_THIS s.main_status_reg &= ~FD_MS_BUSY;
        BX_FD_THIS s.main_status_reg |= FD_MS_MRQ | FD_MS_DIO;
      } else {
        DEV_dma_set_drq(FLOPPY_DMA_CHAN, 1);
      }
      break;

    case 0x4d:
      if ((BX_FD_THIS s.format_count == 0) || BX_FD_THIS s.TC) {
        BX_FD_THIS s.format_count = 0;
        BX_FD_THIS s.status_reg0 = (BX_FD_THIS s.head[drive] << 2) | drive;
        enter_result_phase();
      } else {

        if (!(BX_FD_THIS s.main_status_reg & FD_MS_NDMA)) {
          DEV_dma_set_drq(FLOPPY_DMA_CHAN, 1);
        }
      }
      break;

    case 0xfe:
      theFloppyController->reset(BX_RESET_SOFTWARE);
      BX_FD_THIS s.pending_command = 0;
      BX_FD_THIS s.status_reg0 = 0xc0;
      BX_FD_THIS raise_interrupt();
      BX_FD_THIS s.reset_sensei = 4;
      break;

    case 0x00:
      break;

    default:
      BX_PANIC(("floppy:timer(): unknown case %02x",
        (unsigned) BX_FD_THIS s.pending_command));
  }
}
