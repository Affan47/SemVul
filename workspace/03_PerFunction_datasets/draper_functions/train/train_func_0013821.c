beh_frebebus (listbebus)

struct bebus *listbebus;

  {
  struct bebus *ptbebus;


  while (listbebus != NULL)
    {
    beh_frebiabl  (listbebus->BIABL);
    beh_frebinode (listbebus->BINODE);

    ptbebus   = listbebus;
    listbebus = listbebus->NEXT;
    mbkfree (ptbebus);
    }

  }
