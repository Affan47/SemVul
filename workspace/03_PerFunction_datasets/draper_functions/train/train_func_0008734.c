change_0x84(byte_t changed, byte_t val)
{
  if (changed & 0x01)
    {
      DBG(2, form("KCemu/Ports/4/change/84",
                  "Ports 0x84: display screen %d\n",
                  val & 1));
      memory->displaySCREEN_1(val & 0x01);
    }
  if (changed & 0x02)
    {
      DBG(2, form("KCemu/Ports/4/change/84",
                  "Ports 0x84: pixel/ color %d\n",
                  (val >> 1) & 1));
      memory->enableCOLOR(val & 0x02);
    }
  if (changed & 0x04)
    {
      DBG(2, form("KCemu/Ports/4/change/84",
                  "Ports 0x84: access screen %d\n",
                  (val >> 2) & 1));
      memory->enableSCREEN_1(val & 0x04);
    }
  if (changed & 0x08)
    {
      DBG(2, form("KCemu/Ports/4/change/84",
                  "Ports 0x84: high resolution %d\n",
                  (val >> 3) & 1));
    }
  if (changed & 0xf0)
    {
      DBG(2, form("KCemu/Ports/4/change/84",
                  "Ports 0x84: access RAM8 segment %d\n",
                  (val >> 4) & 0x0f));
      memory->selectRAM_8((val >> 4) & 0x0f);
    }
}
