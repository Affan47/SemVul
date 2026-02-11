instance (ACE_Process_Manager *tm)
{
  ACE_TRACE ("ACE_Process_Manager::instance");
  ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon,
                            *ACE_Static_Object_Lock::instance (), 0));

  ACE_Process_Manager *t = ACE_Process_Manager::instance_;

  ACE_Process_Manager::delete_instance_ = false;


#if defined ACE_HAS_SIG_C_FUNC
  ACE_Object_Manager::at_exit (ACE_Process_Manager::instance_,
                                ACE_Process_Manager_cleanup,
                                0,
                                typeid (*ACE_Process_Manager::instance_).name ());
#else
  ACE_Object_Manager::at_exit (ACE_Process_Manager::instance_,
                                ACE_Process_Manager::cleanup,
                                0,
                                typeid (*ACE_Process_Manager::instance_).name ());
#endif

  ACE_Process_Manager::instance_ = tm;
  return t;
}
