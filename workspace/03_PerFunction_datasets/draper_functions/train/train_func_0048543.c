H5Z_scaleoffset_compress_one_byte(unsigned char *data, size_t data_offset,
    unsigned k, unsigned begin_i, unsigned char *buffer, size_t *j, unsigned *buf_len,
    parms_atomic p, unsigned dtype_len)
{
   unsigned dat_len;
   unsigned char val;


   val = data[data_offset + k];
   if(k == begin_i)
      dat_len = 8 - (dtype_len - p.minbits) % 8;
   else
      dat_len = 8;

   if(*buf_len > dat_len) {
      buffer[*j] |= (unsigned char)((val & ~(~0 << dat_len)) << (*buf_len - dat_len));
      *buf_len -= dat_len;
   } else {
      buffer[*j] |= (unsigned char)((val >> (dat_len - *buf_len)) & ~(~0 << *buf_len));
      dat_len -= *buf_len;
      H5Z_scaleoffset_next_byte(j, buf_len);
      if(dat_len == 0)
          return;

      buffer[*j] = (unsigned char)((val & ~(~0 << dat_len)) << (*buf_len - dat_len));
      *buf_len -= dat_len;
   }
}
