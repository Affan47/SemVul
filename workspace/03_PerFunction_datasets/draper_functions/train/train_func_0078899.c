slotList() const
{
   CK_RV rv;
   CK_SLOT_ID* p11Slots(NULL);
   QList<unsigned long> slotList;
   unsigned long ulNumSlots(0L);


   m_p11->C_GetSlotList(CK_TRUE, p11Slots, &ulNumSlots);
   while (true)
   {
      rv = m_p11->C_GetSlotList(CK_TRUE, p11Slots, &ulNumSlots);
      if (rv != CKR_OK && rv != CKR_BUFFER_TOO_SMALL)
         pk11error("C_GetSlotList", rv);

      if (ulNumSlots == 0)
         break;

      if ((rv == CKR_OK) && p11Slots)
         break;

      p11Slots = reinterpret_cast<CK_SLOT_ID*>(::realloc(p11Slots, ulNumSlots * sizeof (CK_SLOT_ID)));
      ErrorEx::checkOutOfMemory(p11Slots);
   }

   for (unsigned long ul = 0; ul < ulNumSlots; ul++)
   {
      CK_SLOT_INFO slotInfo;
      rv = m_p11->C_GetSlotInfo(p11Slots[ul], &slotInfo);

      if (rv == CKR_OK)
      {
         if ((slotInfo.flags & CKF_TOKEN_PRESENT) == CKF_TOKEN_PRESENT)
            slotList << p11Slots[ul];
      }
   }

   if (p11Slots)
      ::free(p11Slots);

   return(slotList);
}
