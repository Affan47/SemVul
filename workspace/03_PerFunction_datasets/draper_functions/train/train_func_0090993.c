dev_c3725_pcmod_set_nio(vm_instance_t *vm,struct cisco_card *card,
                                   u_int port_id,netio_desc_t *nio)
{
   struct i8255x_data *d = card->drv_info;

   if (!d || (port_id != 0))
      return(-1);

   dev_i8255x_set_nio(d,nio);
   return(0);
}
