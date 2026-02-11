atmsw_create_vpc(atmsw_table_t *t,char *nio_input,u_int vpi_in,
                     char *nio_output,u_int vpi_out)
{
   atmsw_vp_conn_t *swc;
   u_int hbucket;

   ATMSW_LOCK(t);


   if (!(swc = mp_alloc(&t->mp,sizeof(*swc)))) {
      ATMSW_UNLOCK(t);
      return(-1);
   }

   swc->input   = netio_acquire(nio_input);
   swc->output  = netio_acquire(nio_output);
   swc->vpi_in  = vpi_in;
   swc->vpi_out = vpi_out;


   if (!swc->input || !swc->output || atmsw_vp_lookup(t,swc->input,vpi_in))
      goto error;


   if (netio_rxl_add(swc->input,(netio_rx_handler_t)atmsw_recv_cell,
                     t,NULL) == -1)
      goto error;

   hbucket = atmsw_vpc_hash(vpi_in);
   swc->next = t->vp_table[hbucket];
   t->vp_table[hbucket] = swc;
   ATMSW_UNLOCK(t);
   return(0);

 error:
   ATMSW_UNLOCK(t);
   atmsw_release_vpc(swc);
   mp_free(swc);
   return(-1);
}
