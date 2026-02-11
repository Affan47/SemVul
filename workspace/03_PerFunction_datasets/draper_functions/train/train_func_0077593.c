RemoveProcessFromTable( int pid )


{
  WlmProcessSlotType *ps = NULL;


  OFListIterator(WlmProcessSlotType*) it = processTable.begin();
  while ( it != processTable.end() )
  {
    ps = *it;

    if ( ps->processId == pid )
    {
      processTable.remove(*it);
      delete ps;
      return;
    }
    it++;
  }


  DCMWLM_WARN("WlmActivityManager::RemoveProcessFromTable: Could not find process " << pid);
}
