mpc860_fec_update_irq_status(struct mpc860_data *d)
{
   u_int level,siu_bit;

   level = (d->fec_ivec & MPC860_IVEC_ILEVEL_MASK) >> MPC860_IVEC_ILEVEL_SHIFT;
   siu_bit = mpc860_get_siu_lvl(level);

   if (d->fec_ievent & d->fec_imask)
      mpc860_set_pending_irq(d,siu_bit);
   else
      mpc860_clear_pending_irq(d,siu_bit);
}
