dev_c7200_pa_mc8te1_set_nio(vm_instance_t *vm,struct cisco_card *card,
                                u_int port_id,netio_desc_t *nio)
{
   struct pa_mc_data *d = card->drv_info;

   if (!d || (port_id > 0))
      return(-1);

   if (d->nio != NULL)
      return(-1);

   d->nio = nio;


   return(0);
}
