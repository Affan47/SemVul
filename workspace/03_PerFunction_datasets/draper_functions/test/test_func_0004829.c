atmsw_delete_vcc(atmsw_table_t *t,
                     char *nio_input,u_int vpi_in,u_int vci_in,
                     char *nio_output,u_int vpi_out,u_int vci_out)
{
   netio_desc_t *input,*output;
   atmsw_vc_conn_t **swc,*p;
   u_int hbucket;

   ATMSW_LOCK(t);

   input = registry_exists(nio_input,OBJ_TYPE_NIO);
   output = registry_exists(nio_output,OBJ_TYPE_NIO);

   hbucket = atmsw_vcc_hash(vpi_in,vci_in);
   for(swc=&t->vc_table[hbucket];*swc;swc=&(*swc)->next)
   {
      p = *swc;

      if ((p->input == input) && (p->output == output) &&
          (p->vpi_in == vpi_in) && (p->vci_in == vci_in) &&
          (p->vpi_out == vpi_out) && (p->vci_out == vci_out))
      {

         *swc = (*swc)->next;
         ATMSW_UNLOCK(t);

         atmsw_release_vcc(p);
         mp_free(p);
         return(0);
      }
   }

   ATMSW_UNLOCK(t);
   return(-1);
}
