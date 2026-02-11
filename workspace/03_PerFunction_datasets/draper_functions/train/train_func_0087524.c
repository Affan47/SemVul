dev_mueslix_chan_access(cpu_gen_t *cpu,struct mueslix_channel *channel,
                             m_uint32_t offset,u_int op_size,u_int op_type,
                             m_uint64_t *data)
{
   switch(offset) {
      case 0x00:
         if (op_type == MTS_READ) {
            *data = channel->crc_ctrl_reg;
         } else {
            channel->crc_ctrl_reg = *data;

            switch(channel->crc_ctrl_reg) {
               case 0x08:
               case 0x0a:
                  channel->crc_size = channel->crc_ctrl_reg - 0x06;
                  break;

               default:
                  MUESLIX_LOG(channel->parent,"channel %u: unknown value "
                              "for CRC ctrl reg 0x%4.4x\n",
                              channel->id,channel->crc_ctrl_reg);

                  channel->crc_size = 2;
            }
            MUESLIX_LOG(channel->parent,
                        "channel %u: CRC size set to 0x%4.4x\n",
                        channel->id,channel->crc_size);
         }
         break;

      case 0x40:
         if (op_type == MTS_READ)
            *data = channel->clk_shift;
         else
            channel->clk_shift = *data;


         dev_mueslix_update_clk_rate(channel);
         break;

      case 0x44:
         if (op_type == MTS_READ)
            *data = channel->clk_div;
         else
            channel->clk_div = *data;
         break;

      case 0x60:
         if ((op_type == MTS_READ) && (channel->nio != NULL))
            *data = 0xFFFFFFFF;
         break;

      case 0x64:
         if (op_type == MTS_READ)
            *data = 0x7B;
         break;

      case 0x90:
         if (op_type == MTS_READ)
            *data = 0x11111111;
         break;

      case 0x80:
         if (op_type == MTS_WRITE)
            channel->tx_start = channel->tx_current = *data;
         else
            *data = channel->tx_start;
         break;

      case 0x84:
         if (op_type == MTS_WRITE)
            channel->tx_end = *data;
         else
            *data = channel->tx_end;
         break;

      case 0x88:
         if (op_type == MTS_WRITE)
            channel->rx_start = channel->rx_current = *data;
         else
            *data = channel->rx_start;
         break;

      case 0x8c:
         if (op_type == MTS_WRITE)
            channel->rx_end = *data;
         else
            *data = channel->rx_end;
         break;

#if DEBUG_UNKNOWN
      default:
         if (op_type == MTS_WRITE) {
            MUESLIX_LOG(channel->parent,"channel %u: "
                        "write to unknown addr 0x%4.4x, value=0x%llx\n",
                        channel->id,offset,*data);
         }
#endif
   }
}
