mv64460_eth_update_pice(struct mv64460_data *d,
                                    struct eth_port *port)
{
   if (port->pice & port->peim & MV64460_ETH_ICE_SUM_MASK) {
      port->pice |= MV64460_ETH_ICE_SUM;
   } else {
      port->pice &= ~MV64460_ETH_ICE_SUM;
   }

   if (port->pice) {
      port->pic |= MV64460_ETH_IC_EXTEND;
   } else {
      port->pic &= ~MV64460_ETH_IC_EXTEND;
   }

   mv64460_eth_update_pic(d,port);
}
