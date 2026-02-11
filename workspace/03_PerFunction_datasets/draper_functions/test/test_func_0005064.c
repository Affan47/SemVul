operator delete(void * addr)
{
  if (corpse_lock)
  {
    GCriticalSectionLock lock(corpse_lock);


    if (corpse_tail)
    {
      corpse_tail->next=new DjVuPortCorpse((DjVuPort *) addr);
      corpse_tail=corpse_tail->next;
      corpse_tail->next=0;
    } else
    {
      corpse_head=corpse_tail=new DjVuPortCorpse((DjVuPort *) addr);
      corpse_tail->next=0;
    }
    corpse_num++;
    if (corpse_num>=MAX_CORPSE_NUM)
    {
      DjVuPortCorpse * corpse=corpse_head;
      corpse_head=corpse_head->next;
      delete corpse;
      corpse_num--;
    }
  }
  ::operator delete(addr);
}
