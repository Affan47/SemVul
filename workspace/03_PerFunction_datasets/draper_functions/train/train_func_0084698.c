mpc860_idma_fetch_bd(struct mpc860_data *d,m_uint16_t bd_addr,
                                struct mpc860_idma_bd *bd)
{
   if ((bd_addr < MPC860_DPRAM_OFFSET) || (bd_addr > MPC860_DPRAM_END))
      return(-1);

   bd->offset = bd_addr - MPC860_DPRAM_OFFSET;


   bd->ctrl = dpram_r16(d,bd->offset+0x00);


   bd->dfcr = dpram_r8(d,bd->offset+0x02);
   bd->sfcr = dpram_r8(d,bd->offset+0x03);


   bd->buf_len = dpram_r32(d,bd->offset+0x04);
   bd->src_bp  = dpram_r32(d,bd->offset+0x08);
   bd->dst_bp  = dpram_r32(d,bd->offset+0x0c);

#if DEBUG_IDMA
   MPC_LOG(d,"fetched IDMA BD at 0x%4.4x, src_bp=0x%8.8x, dst_bp=0x%8.8x "
           "len=%d\n",bd->offset,bd->src_bp,bd->dst_bp,bd->buf_len);
#endif

   return(0);
}
