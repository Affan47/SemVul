atmsw_vc_lookup(atmsw_table_t *t,netio_desc_t *input,
                                 u_int vpi,u_int vci)
{
   atmsw_vc_conn_t *swc;

   for(swc=t->vc_table[atmsw_vcc_hash(vpi,vci)];swc;swc=swc->next)
      if ((swc->input == input) && (swc->vpi_in == vpi) &&
          (swc->vci_in == vci))
         return swc;

   return NULL;
}
