add_ioapic (imps_ioapic * ioapic)
{
  KERNEL_PRINT (("  I/O APIC id %d ver %d, address: 0x%x  ",
		 ioapic->id, ioapic->ver, ioapic->addr));
  if (!(ioapic->flags & IMPS_FLAG_ENABLED))
    {
      KERNEL_PRINT (("DISABLED\n"));
      return;
    }
  KERNEL_PRINT (("\n"));


}
