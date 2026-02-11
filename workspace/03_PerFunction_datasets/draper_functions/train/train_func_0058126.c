dev_i8255x_cu_resume(struct i8255x_data *d)
{
   struct i8255x_cu_action action;
   m_uint32_t cu_addr;


   if (d->cu_state == CU_STATE_IDLE)
      return(FALSE);

   cu_addr = d->cu_base + d->cu_offset;


   dev_i8255x_fetch_cb(d,cu_addr,&action);

   if (action.ctrl & CB_CTRL_S)
      return(FALSE);

   d->cu_offset = action.link_offset;
   d->cu_state  = CU_STATE_LPQ_ACT;
   dev_i8255x_process_cbl(d);
   return(TRUE);
}
