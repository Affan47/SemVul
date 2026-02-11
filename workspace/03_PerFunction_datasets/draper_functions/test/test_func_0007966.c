instance (size_t size)
{
  ACE_TRACE ("ACE_Service_Repository::instance");

  if (ACE_Service_Repository::svc_rep_ == 0)
    {

      ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon,
                                *ACE_Static_Object_Lock::instance (), 0));
      if (ACE_Service_Repository::svc_rep_ == 0)
        {
          if (ACE_Object_Manager::starting_up () ||
              !ACE_Object_Manager::shutting_down ())
            {
              ACE_NEW_RETURN (ACE_Service_Repository::svc_rep_,
                              ACE_Service_Repository (size),
                              0);
              ACE_Service_Repository::delete_svc_rep_ = true;
            }
        }
    }

  return ACE_Service_Repository::svc_rep_;
}
