ioapic_init(void)
{
  int i, id, maxintr;

  if(!ismp)
    return;

  ioapic = (volatile struct ioapic*)IOAPIC;
  maxintr = (ioapic_read(REG_VER) >> 16) & 0xFF;
  id = ioapic_read(REG_ID) >> 24;
  if(id != ioapic_id)
    cprintf("ioapic_init: id isn't equal to ioapic_id; not a MP\n");


  for(i = 0; i <= maxintr; i++){
    ioapic_write(REG_TABLE+2*i, INT_DISABLED | (IRQ_OFFSET + i));
    ioapic_write(REG_TABLE+2*i+1, 0);
  }
}
