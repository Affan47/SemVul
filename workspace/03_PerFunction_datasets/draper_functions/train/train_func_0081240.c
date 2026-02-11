at_exit (void *object,
                                ACE_CLEANUP_FUNC cleanup_hook,
                                void *param)
{
  ACE_TRACE ("ACE_Thread_Descriptor::at_exit");


  if (cleanup_hook == 0)
   {
     if (this->at_exit_list_!= 0)
      this->at_pop(0);
   }
  else
   {
     ACE_At_Thread_Exit* cleanup = 0;
     ACE_NEW_RETURN (cleanup,
                     ACE_At_Thread_Exit_Func (object,
                                              cleanup_hook,
                                              param),
                     -1);
     this->at_push (cleanup);
   }
  return 0;
}
