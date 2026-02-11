fretab (pt_hash)

struct entry **pt_hash;
  {
  struct entry *pt_entry;
  int           i       ;

  if (pt_hash != NULL)
    {
    for (i=0 ; i<PAT_HSZDFN ; i++)
      {
      if ((pt_entry = pt_hash[i]) != NULL)
        {
        while (pt_entry->next != NULL)
          pt_entry = pt_entry->next;

        pt_entry->next = ENTRY_HEAD ;
        ENTRY_HEAD     = pt_hash [i];
        }
      }
    mbkfree (pt_hash);
    }
  }
