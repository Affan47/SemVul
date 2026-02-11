dev_c3725_pcmod_unset_nio(vm_instance_t *vm,struct cisco_card *card,
                                     u_int port_id)
{
   struct i8255x_data *d = card->drv_info;

   if (!d || (port_id != 0))
      return(-1);

   dev_i8255x_unset_nio(d);
   return(0);
}
