dev_i8255x_access(cpu_gen_t *cpu,struct vdevice *dev,
                        m_uint32_t offset,u_int op_size,u_int op_type,
                        m_uint64_t *data)
{
   struct i8255x_data *d = dev->priv_data;
   u_int cuc,ruc,mii_op;

   if (op_type == MTS_READ)
      *data = 0x0;

#if DEBUG_ACCESS
   if (op_type == MTS_READ) {
      cpu_log(cpu,d->name,"read  access to offset=0x%x, pc=0x%llx, size=%u\n",
              offset,cpu_get_pc(cpu),op_size);
   } else {
      cpu_log(cpu,d->name,"write access to offset=0x%x, pc=0x%llx, "
              "val=0x%llx, size=%u\n",offset,cpu_get_pc(cpu),*data,op_size);
   }
#endif

   EEPRO_LOCK(d);

   switch(offset) {

      case 0x00:
         if (op_type == MTS_WRITE)
            d->scb_ic = *data;
         break;


      case 0x01:
         if (op_type == MTS_WRITE) {
            cuc = (*data & SCB_CMD_CUC_MASK) >> SCB_CMD_CUC_SHIFT;
            ruc = (*data & SCB_CMD_RUC_MASK) >> SCB_CMD_RUC_SHIFT;


            dev_i8255x_process_cu_cmd(d,cuc);
            dev_i8255x_process_ru_cmd(d,ruc);
         }
         break;


      case 0x02:
         if (op_type == MTS_READ) {
            *data  = d->scb_stat_ack << 8;
         } else {
            d->scb_stat_ack &= ~(*data >> 8);
            dev_i8255x_update_irq_status(d);
         }
         break;


      case 0x04:
         if (op_type == MTS_WRITE)
            d->scb_gptr = *data;
         else
            *data = d->scb_gptr;
         break;


      case 0x10:
         if (op_type == MTS_READ) {
            mii_op = (d->mii_ctrl & I8255X_MDI_OP_MASK) >> I8255X_MDI_OP_SHIFT;

            if (mii_op == MII_OPCODE_READ) {
               d->mii_ctrl &= ~I8255X_MDI_DATA_MASK;
               d->mii_ctrl |= mii_reg_read(d);
            }

            *data = d->mii_ctrl | I8255X_MDI_R;
         } else {
            d->mii_ctrl = *data;

            mii_op = (d->mii_ctrl & I8255X_MDI_OP_MASK) >> I8255X_MDI_OP_SHIFT;
            if (mii_op == MII_OPCODE_WRITE)
               mii_reg_write(d);
         }
         break;

#if DEBUG_UNKNOWN
      default:
         if (op_type == MTS_READ) {
            cpu_log(cpu,d->name,
                    "read access to unknown offset=0x%x, "
                    "pc=0x%llx (size=%u)\n",
                    offset,cpu_get_pc(cpu),op_size);
         } else {
            cpu_log(cpu,d->name,
                    "write access to unknown offset=0x%x, pc=0x%llx, "
                    "val=0x%llx (size=%u)\n",
                    offset,cpu_get_pc(cpu),*data,op_size);
         }
#endif
   }

   EEPRO_UNLOCK(d);
   return NULL;
}
