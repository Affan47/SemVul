fs_nvram_clear(fs_nvram_t *fs, u_int offset, u_int len)
{
   u_int i;

   for (i = 0; i < len; i++) {
      fs->write_byte(fs, offset + i, 0);
   }
}
