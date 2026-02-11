dev_plx9054_access(cpu_gen_t *cpu,struct vdevice *dev,
                         m_uint32_t offset,u_int op_size,u_int op_type,
                         m_uint64_t *data)
{
   struct plx_data *d = dev->priv_data;

   if (op_type == MTS_READ)
      *data = 0;

   switch(offset) {

      case 0xF0:
         if (op_type == MTS_WRITE) {
            d->lspc[1].range = *data;
            plx_map_space(d,1);
         } else {
            *data = d->lspc[1].range;
         }
         break;

      default:
         return(dev_plx_access(cpu,dev,offset,op_size,op_type,data));
   }

   return NULL;
}
