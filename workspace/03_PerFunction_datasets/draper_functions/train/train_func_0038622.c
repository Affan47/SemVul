disconnect610p (void)
{
  int control, i;

  Outb (CONTROL, 0x04);
  for (i = 0; i < 41; i++)
    {
      control = Inb (CONTROL) & 0x3F;
      if (control != 0x04)
	{
	  DBG (0, "disconnect610p failed (idx %d=%02X)! (%s:%d)\n",
	       i, control, __FILE__, __LINE__);
	  return 0;
	}
    }
  Outb (CONTROL, 0x0C);
  control = Inb (CONTROL) & 0x3F;
  if (control != 0x0C)
    {
      DBG (0, "disconnect610p failed expected 0x0C got %02X (%s:%d)\n",
	   control, __FILE__, __LINE__);
      return 0;
    }

  Outb (DATA, 0xFF);
  return 1;
}
