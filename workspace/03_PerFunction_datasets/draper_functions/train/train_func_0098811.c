write_handler(void *this_ptr, Bit32u address, Bit32u value, unsigned io_len)
{
#if !BX_USE_DEV_SMF
  bx_devices_c *class_ptr = (bx_devices_c *) this_ptr;
  class_ptr->port92_write(address, value, io_len);
}

void bx_devices_c::port92_write(Bit32u address, Bit32u value, unsigned io_len)
{
#else
  UNUSED(this_ptr);
#endif

  BX_DEBUG(("port92h write of %02x partially supported!!!", (unsigned) value));
  BX_DEBUG(("A20: set_enable_a20() called"));
  BX_SET_ENABLE_A20((value & 0x02) >> 1);
  BX_DEBUG(("A20: now %u", (unsigned) BX_GET_ENABLE_A20()));
  if (value & 0x01) {
    BX_INFO(("iowrite to port0x92 : reset resquested"));
    bx_pc_system.Reset(BX_RESET_SOFTWARE);
  }
}
