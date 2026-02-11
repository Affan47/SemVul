sbft_reset(UtilStringBuffer * sb)
{
   if (sb->max)
      *((char *) sb->hdl) = 0;
   sb->len = 0;
}
