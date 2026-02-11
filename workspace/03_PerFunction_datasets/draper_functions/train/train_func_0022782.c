bcm5600_mii_write(struct nm_16esw_data *d)
{
   m_uint8_t port,reg;
   m_uint16_t isolation;

   port = (d->mii_input >> 16) & 0xFF;
   reg  = (d->mii_input >> 24) & 0xFF;

   if ((port < 32) && (reg < 32))
   {
#if DEBUG_MII
      BCM_LOG(d,"MII: port 0x%4.4x, reg 0x%2.2x: writing 0x%4.4x\n",
              port,reg,d->mii_input & 0xFFFF);
#endif


      if (reg == 0) {
         isolation = (d->mii_input ^ d->mii_regs[port][reg]) & 0x400;

         if (isolation) {
#if DEBUG_MII
            BCM_LOG(d,"MII: port 0x%4.4x: generating IRQ\n",port);
#endif
            d->mii_intr = TRUE;
            pci_dev_trigger_irq(d->vm,d->pci_dev);
         }
      }

      d->mii_regs[port][reg] = d->mii_input & 0xFFFF;
   }
}
