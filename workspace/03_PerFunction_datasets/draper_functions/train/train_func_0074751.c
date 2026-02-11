bcm5600_mii_read(struct nm_16esw_data *d)
{
   m_uint8_t port,reg;

   port = (d->mii_input >> 16) & 0xFF;
   reg  = (d->mii_input >> 24) & 0xFF;

   if ((port < 32) && (reg < 32)) {
      d->mii_output = d->mii_regs[port][reg];

      switch(reg) {
         case 0x00:
            d->mii_output &= ~0x8200;
            break;
         case 0x01:
            if (d->ports[port].nio && bcm5600_mii_port_status(d,port))
               d->mii_output = 0x782C;
            else
               d->mii_output = 0;
            break;
         case 0x02:
            d->mii_output = 0x40;
            break;
         case 0x03:
            d->mii_output = 0x61d4;
            break;
         case 0x04:
            d->mii_output = 0x1E1;
            break;
         case 0x05:
            d->mii_output = 0x41E1;
            break;
         default:
            d->mii_output = 0;
      }
   }
}
