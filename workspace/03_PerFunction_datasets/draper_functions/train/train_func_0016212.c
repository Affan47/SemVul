pci_plx_write(cpu_gen_t *cpu,struct pci_device *dev,
                          int reg,m_uint32_t value)
{
   struct plx_data *d = dev->priv_data;

#if DEBUG_ACCESS
   PLX_LOG(d,"write 0x%x to PLX PCI register 0x%x\n",value,reg);
#endif

   switch(reg) {

      case PCI_REG_BAR0:
         vm_map_device(cpu->vm,&d->plx_dev,(m_uint64_t)value);
         PLX_LOG(d,"PLX registers are mapped at 0x%x\n",value);
         break;


      case PCI_REG_BAR2:
         d->lspc[0].lbaddr = value;
         plx_map_space(d,0);
         break;
   }
}
