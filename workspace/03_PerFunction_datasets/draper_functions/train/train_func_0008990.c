operator new (size_t sz)
{
  if (!corpse_lock) corpse_lock=new GCriticalSection();


  void * addr=0;
  {
    GCriticalSectionLock lock(corpse_lock);


    int addr_num=0;
    static void * addr_arr[MAX_CORPSE_NUM];


    for(int attempt=0;attempt<MAX_CORPSE_NUM;attempt++)
    {
      void * test_addr=::operator new (sz);
      addr_arr[addr_num++]=test_addr;


      DjVuPortCorpse * corpse;
      for(corpse=corpse_head;corpse;corpse=corpse->next)
        if (test_addr==corpse->port) break;
        if (!corpse)
        {
          addr=test_addr;
          addr_num--;
          break;
        }
    }


    if (!addr) addr=::operator new(sz);


    addr_num--;
    while(addr_num>=0) ::operator delete(addr_arr[addr_num--]);
  }

  DjVuPortcaster * pcaster=get_portcaster();
  GCriticalSectionLock lock(&pcaster->map_lock);
  pcaster->cont_map[addr]=0;
  return addr;
}
