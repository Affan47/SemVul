pci_pos_write(cpu_gen_t *cpu,struct pci_device *dev,
                          int reg,m_uint32_t value)
{
   struct pa_mc_data *d = dev->priv_data;

#if DEBUG_ACCESS
   PA_MC_LOG(d,"write 0x%x to PCI register 0x%x\n",value,reg);
#endif

   switch(reg) {
      case PCI_REG_BAR0:

         PA_MC_LOG(d,"registers are mapped at 0x%x\n",value);
         break;
   }
}
