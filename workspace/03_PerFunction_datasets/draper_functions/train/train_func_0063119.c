fini (void)
{
  ACE_TRACE ("ACE_Service_Repository::fini");
  ACE_MT (ACE_GUARD_RETURN (ACE_Recursive_Thread_Mutex, ace_mon, this->lock_, -1));

  int retval = 0;


#ifndef ACE_NLOGGING
  if (ACE::debug ())
  {
    for (size_t i = this->service_array_.size (); i-- != 0;)
    {
      ACE_Service_Type *s =
        const_cast<ACE_Service_Type *> (this->service_array_[i]);
      if (s == 0)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("ACE (%P|%t) SR::fini, repo=%@ [%d] -> 0\n"),
                    this,
                    i));
    }
  }
#endif


  for (size_t i = this->service_array_.size (); i-- != 0;)
  {

    ACE_Service_Type *s =
      const_cast<ACE_Service_Type *> (this->service_array_[i]);

    if (s != 0 &&
        s->type () != 0 &&
        (s->type ()->service_type () != ACE_Service_Type::MODULE))
    {
#ifndef ACE_NLOGGING
      if (ACE::debug ())
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("ACE (%P|%t) SR::fini, repo=%@ [%d], ")
                    ACE_TEXT ("name=%s, type=%@, object=%@, active=%d\n"),
                    this,
                    i,
                    s->name (),
                    s->type (),
                    (s->type () != 0) ? s->type ()->object () : 0,
                    s->active ()));
      }
#endif


      retval += s->fini ();
    }
  }


  for (size_t i = this->service_array_.size (); i-- != 0;)
  {

    ACE_Service_Type *s =
      const_cast<ACE_Service_Type *> (this->service_array_[i]);

    if (s != 0 &&
        s->type () != 0 &&
        (s->type ()->service_type () == ACE_Service_Type::MODULE))
    {
#ifndef ACE_NLOGGING
      if (ACE::debug ())
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("ACE (%P|%t) SR::fini, repo=%@ [%d], ")
                    ACE_TEXT ("name=%s, type=%@, object=%@, active=%d\n"),
                    this,
                    i,
                    s->name (),
                    s->type (),
                    (s->type () != 0) ? s->type ()->object () : 0,
                    s->active ()));
      }
#endif

      retval += s->fini ();
    }
  }
  return (retval == 0) ? 0 : -1;
}
