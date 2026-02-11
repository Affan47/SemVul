hpmud_probe_devices(enum HPMUD_BUS_ID bus, char *buf, int buf_size, int *cnt, int *bytes_read)
{
   int len=0;

   DBG("[%d] hpmud_probe_devices() bus=%d\n", getpid(), bus);

   buf[0] = 0;
   *cnt = 0;

   if (bus == HPMUD_BUS_USB)
   {
      len = musb_probe_devices(buf, buf_size, cnt);
   }
#ifdef HAVE_PPORT
   else if (bus == HPMUD_BUS_PARALLEL)
   {
      len = pp_probe_devices(buf, buf_size, cnt);
   }
#endif
   else if (bus == HPMUD_BUS_ALL)
   {
      len = musb_probe_devices(buf, buf_size, cnt);
#ifdef HAVE_PPORT
      len += pp_probe_devices(buf+len, buf_size-len, cnt);
#endif
   }

   *bytes_read = len;

   return HPMUD_R_OK;
}
