netio_desc_create_tap(char *nio_name,char *tap_name)
{
   netio_tap_desc_t *ntd;
   netio_desc_t *nio;

   if (!(nio = netio_create(nio_name)))
      return NULL;

   ntd = &nio->u.ntd;

   if (netio_tap_create(ntd,tap_name) == -1) {
      netio_free(nio,NULL);
      return NULL;
   }

   nio->type     = NETIO_TYPE_TAP;
   nio->send     = (void *)netio_tap_send;
   nio->recv     = (void *)netio_tap_recv;
   nio->free     = (void *)netio_tap_free;
   nio->save_cfg = netio_tap_save_cfg;
   nio->dptr     = &nio->u.ntd;

   if (netio_record(nio) == -1) {
      netio_free(nio,NULL);
      return NULL;
   }

   return nio;
}
