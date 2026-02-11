addOverlay(DcmItem& overlayIOD, Uint16 groupInItem, Uint16 newGroup)
{
  if ((groupInItem < 0x6000)||(groupInItem > 0x601F)) return EC_IllegalCall;
  if ((newGroup < 0x6000)||(newGroup > 0x601F)) return EC_IllegalCall;
  if (haveOverlayGroup(newGroup)) return EC_IllegalCall;

  DcmStack stack;
  DcmTagKey key(groupInItem,0x3000);
  DVPSOverlay *newOverlay = NULL;

  OFCondition result = overlayIOD.search(key, stack, ESM_fromHere, OFFalse);
  if (EC_Normal == result)
  {
    newOverlay = new DVPSOverlay();
    if (newOverlay)
    {
      result = newOverlay->read(overlayIOD,(Uint8)(groupInItem-0x6000), (Uint8)(newGroup-0x6000));
      if (EC_Normal==result) list_.push_back(newOverlay); else delete newOverlay;
    } else result = EC_MemoryExhausted;
  }
  return result;
}
