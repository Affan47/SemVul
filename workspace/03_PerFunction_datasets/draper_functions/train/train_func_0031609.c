sdl_get_temp_buff(sdl_data* sd, int size)
{
  if (size > TEMP_BINARY_SIZE) {
    return sdl_getbuff(sd, size);
  } else {
    ErlDrvBinary* bin = (ErlDrvBinary *) sd->temp_bin;
    driver_binary_inc_refc(bin);
    sd->buff = bin;
    sd->len = size;
    return bin->orig_bytes;
  }
}
