FindInstanceTemplateSlot(
  void *theEnv,
  DEFCLASS *cls,
  SYMBOL_HN *sname)
  {
   int sid;

   sid = FindSlotNameID(theEnv,sname);
   if (sid == -1)
     return(-1);
   if (sid > (int) cls->maxSlotNameID)
     return(-1);
   return((int) cls->slotNameMap[sid] - 1);
  }
