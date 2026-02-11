beh_fretab (pt_hash)

struct beden **pt_hash;

  {
  struct beden *pt_entry   ;
  struct beden *pt_nxtentry;
  struct bedrd *pt_record  ;
  long           i          ;

  if (pt_hash != NULL)
    {
    for (i=0 ; i<BEH_HSZDFN ; i++)
      {
      if ((pt_entry = pt_hash [i]) != NULL)
        {
        while (pt_entry != NULL)
          {
          pt_record = pt_entry->DATA;

          while (pt_record->NEXT != NULL)
            pt_record = pt_record->NEXT;

          pt_record->NEXT = BEH_DCRHED;
          BEH_DCRHED      = pt_entry->DATA;

          pt_nxtentry     = pt_entry->NEXT;
          pt_entry->NEXT  = BEH_DCEHED;
          BEH_DCEHED      = pt_entry;
          pt_entry        = pt_nxtentry;
          }
        }
      }
    mbkfree (pt_hash);
    }
  }
