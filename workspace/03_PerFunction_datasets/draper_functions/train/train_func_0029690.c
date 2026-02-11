find_hthread (ACE_hthread_t h_id)
{
  for (ACE_Double_Linked_List_Iterator<ACE_Thread_Descriptor> iter (this->thr_list_);
       !iter.done ();
       iter.advance ())
    {
      if (ACE_OS::thr_cmp (iter.next ()->thr_handle_, h_id))
        {
          return iter.next ();
        }
    }

  return 0;
}
