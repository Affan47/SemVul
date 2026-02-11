synth_setpatch (int voice, guint8 *data)
{
  int i;

  opl_write(0xBD, 0);

  for (i = 0; i < 10; i++)
    opl_write(register_base[i] + register_offset[voice], data[i]);

  opl_write(register_base[10] + voice, data[10]);


  opl_write_L(0xb0 + voice, adlib_reg_L[0xb0+voice] & 0xdf);
  opl_write_R(0xb0 + voice, adlib_reg_R[0xb0+voice] & 0xdf);

#ifdef DEBUG_ADLIB
  for (i = 0; i < 10; i++)
    printf("%02x ", adlib_reg_L[register_base[i]+register_offset[voice]]);
    printf("%02x ", adlib_reg_L[register_base[10]+voice]);
#endif

}
