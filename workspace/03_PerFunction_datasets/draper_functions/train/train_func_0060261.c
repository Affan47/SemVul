idle_tid_list_push_back(uint32_t ptid, uint32_t tid)
{
  IdleThreadIdListEntryT* idle_tid;

  vt_libassert(ptid < VTThrdMaxNum);


  idle_tid = (IdleThreadIdListEntryT*)calloc(1,
               sizeof(IdleThreadIdListEntryT));
  if (idle_tid == NULL)
    vt_error();

  idle_tid->tid = tid;


  if (idleThreadIds[ptid].last)
  {
    idleThreadIds[ptid].last->next = idle_tid;
    idleThreadIds[ptid].last = idle_tid;
  }
  else
  {
    idleThreadIds[ptid].first = idleThreadIds[ptid].last = idle_tid;
  }


  idleThreadIds[ptid].size++;
}
