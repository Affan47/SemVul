e_ipc_codec_str_4int_dec(char *data, int bytes, E_Ipc_Str_4Int **dest)
{
  E_Ipc_Str_4Int *dat;

  if (!data) return 0;
  dat = eet_data_descriptor_decode(_e_ipc_str_4int_edd, data, bytes);
  if (!dat) return 0;
  if (dest) *dest = dat;
  return 1;
}
