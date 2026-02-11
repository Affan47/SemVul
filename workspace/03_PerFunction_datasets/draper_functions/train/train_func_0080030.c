dev_c1700_mb_eth_set_nio(vm_instance_t *vm,struct cisco_card *card,
                                    u_int port_id,netio_desc_t *nio)
{
   struct mpc860_data *d = card->drv_info;

   if (port_id != 0)
      return(-1);

   return(mpc860_fec_set_nio(d,nio));
}
