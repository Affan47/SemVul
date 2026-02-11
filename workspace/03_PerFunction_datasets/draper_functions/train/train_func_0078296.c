write_handler(void *this_ptr, Bit32u address, Bit32u dvalue, unsigned io_len)
{
#if !BX_USE_PIT_SMF
  bx_pit_c *class_ptr = (bx_pit_c *) this_ptr;
  class_ptr->write(address, dvalue, io_len);
}

void bx_pit_c::write(Bit32u address, Bit32u dvalue, unsigned io_len)
{
#else
  UNUSED(this_ptr);
#endif
  Bit8u   value;
  Bit64u my_time_usec = bx_virt_timer.time_usec();
  Bit64u time_passed = my_time_usec-BX_PIT_THIS s.last_usec;
  Bit32u time_passed32 = (Bit32u)time_passed;

  if(time_passed32) {
    periodic(time_passed32);
  }
  BX_PIT_THIS s.last_usec=BX_PIT_THIS s.last_usec + time_passed;

  value = (Bit8u) dvalue;

  BX_DEBUG(("write to port 0x%04x, value = 0x%02x", address, value));

  switch (address) {
    case 0x40:
      BX_PIT_THIS s.timer.write(0, value);
      break;

    case 0x41:
      BX_PIT_THIS s.timer.write(1, value);
      break;

    case 0x42:
      BX_PIT_THIS s.timer.write(2, value);
      break;

    case 0x43:
      BX_PIT_THIS s.timer.write(3, value);
      break;

    case 0x61:
      BX_PIT_THIS s.speaker_data_on = (value >> 1) & 0x01;
      if (BX_PIT_THIS s.speaker_data_on) {
        DEV_speaker_beep_on((float)(1193180.0 / BX_PIT_THIS get_timer(2)));
      } else {
        DEV_speaker_beep_off();
      }

      BX_PIT_THIS s.timer.set_GATE(2, value & 0x01);
      break;

    default:
      BX_PANIC(("unsupported io write to port 0x%04x = 0x%02x", address, value));
  }

  if(time_passed || (BX_PIT_THIS s.last_next_event_time != BX_PIT_THIS s.timer.get_next_event_time()))
  {
    BX_DEBUG(("RESETting timer"));
    bx_virt_timer.deactivate_timer(BX_PIT_THIS s.timer_handle[0]);
    BX_DEBUG(("deactivated timer"));
    if(BX_PIT_THIS s.timer.get_next_event_time()) {
      bx_virt_timer.activate_timer(BX_PIT_THIS s.timer_handle[0],
                                   (Bit32u)BX_MAX(1,TICKS_TO_USEC(BX_PIT_THIS s.timer.get_next_event_time())),
                                   0);
      BX_DEBUG(("activated timer"));
    }
    BX_PIT_THIS s.last_next_event_time = BX_PIT_THIS s.timer.get_next_event_time();
  }
  BX_DEBUG(("s.last_usec="FMT_LL"d",BX_PIT_THIS s.last_usec));
  BX_DEBUG(("s.timer_id=%d",BX_PIT_THIS s.timer_handle[0]));
  BX_DEBUG(("s.timer.get_next_event_time=%x",BX_PIT_THIS s.timer.get_next_event_time()));
  BX_DEBUG(("s.last_next_event_time=%d",BX_PIT_THIS s.last_next_event_time));

}
