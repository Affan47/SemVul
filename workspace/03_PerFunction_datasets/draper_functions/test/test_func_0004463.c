EPPconnect (void)
{
  int control;
  int data;


  Outb (DATA, 0x04);
  Outb (CONTROL, 0x0C);

  data = Inb (DATA);
  control = Inb (CONTROL);
  Outb (CONTROL, control & 0x1F);
  control = Inb (CONTROL);
  Outb (CONTROL, control & 0x1F);

  if (sendCommand (0xE0) != 1)
    {
      DBG (0, "EPPconnect: sendCommand(0xE0) failed! (%s:%d)\n", __FILE__,
	   __LINE__);
      return 0;
    }
  ClearRegister (0);
  init001 ();
  return 1;
}
