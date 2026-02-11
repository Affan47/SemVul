mpc860_idma_start_channel(struct mpc860_data *d,u_int id)
{
   struct mpc860_idma_bd bd;
   m_uint16_t dma_base,bd_offset;

   switch(id) {
      case 0:
         dma_base = MPC860_IDMA1_BASE;
         break;
      case 1:
         dma_base = MPC860_IDMA2_BASE;
         break;
      default:
         return(-1);
   }


   bd_offset = dpram_r16(d,dma_base+0x00);

   while(1) {

      if (mpc860_idma_fetch_bd(d,bd_offset,&bd) == -1)
         return(-1);

      if (!(bd.ctrl & MPC860_IDMA_CTRL_V)) {
         d->idsr[id] |= MPC860_IDSR_OB;
         break;
      }


      mpc860_idma_transfer(d,&bd);


      bd.ctrl &= ~MPC860_IDMA_CTRL_V;
      dpram_w16(d,bd_offset-MPC860_DPRAM_OFFSET+0x00,bd.ctrl);


      if (bd.ctrl & MPC860_IDMA_CTRL_I)
         d->idsr[id] |= MPC860_IDSR_AD;


      if (bd.ctrl & MPC860_IDMA_CTRL_L) {
         d->idsr[id] |= MPC860_IDSR_DONE;
         break;
      }

      bd_offset += sizeof(MPC860_IDMA_BD_SIZE);
   }

   mpc860_idma_update_idsr(d,id);
   return(0);
}
