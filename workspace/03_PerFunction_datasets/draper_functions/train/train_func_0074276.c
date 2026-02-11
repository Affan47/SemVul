atmsw_handle_cell(atmsw_table_t *t,netio_desc_t *input,
                          m_uint8_t *cell)
{
   m_uint32_t atm_hdr,vpi,vci;
   netio_desc_t *output = NULL;
   atmsw_vp_conn_t *vpc;
   atmsw_vc_conn_t *vcc;
   ssize_t len;


   atm_hdr = m_ntoh32(cell);

   vpi = (atm_hdr & ATM_HDR_VPI_MASK) >> ATM_HDR_VPI_SHIFT;
   vci = (atm_hdr & ATM_HDR_VCI_MASK) >> ATM_HDR_VCI_SHIFT;


   if ((vpc = atmsw_vp_lookup(t,input,vpi)) != NULL) {
      atmsw_vp_switch(vpc,cell);
      output = vpc->output;
   } else {

      if ((vcc = atmsw_vc_lookup(t,input,vpi,vci)) != NULL) {
         atmsw_vc_switch(vcc,cell);
         output = vcc->output;
      }
   }

   len = netio_send(output,cell,ATM_CELL_SIZE);

   if (len != ATM_CELL_SIZE) {
      t->cell_drop++;
      return(-1);
   }

   return(0);
}
