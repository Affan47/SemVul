open (key_t k,
                                short create,
                                int initial_value,
                                u_short nsems,
                                mode_t perms)
{
  ACE_TRACE ("ACE_SV_Semaphore_Complex::open");
  if (k == IPC_PRIVATE)
    return -1;

  this->key_ = k;


  this->sem_number_ = nsems + 2;

  if (create == ACE_SV_Semaphore_Complex::ACE_CREATE)
    {
      int result;

      do
        {
          this->internal_id_ = ACE_OS::semget
            (this->key_,
             (u_short) 2 + nsems,
             perms | ACE_SV_Semaphore_Complex::ACE_CREATE);

          if (this->internal_id_ == -1)
            return -1;


          result = ACE_OS::semop (this->internal_id_,
                                  &ACE_SV_Semaphore_Complex::op_lock_[0],
                                  2);
        }
      while (result == -1 && (errno == EINVAL || errno == EIDRM));

      if (result == -1)
        return -1;


      int semval = ACE_SV_Semaphore_Simple::control (GETVAL, 0, 1);

      if (semval == -1)
        return this->init ();
      else if (semval == 0)
        {


          if (ACE_SV_Semaphore_Simple::control (SETVAL,
                                                ACE_SV_Semaphore_Complex::BIGCOUNT_,
                                                1) == -1)
            return -1;
          else
            for (u_short i = 0; i < nsems; i++)
              if (this->control (SETVAL, initial_value, i) == -1)
                return -1;
        }


      return ACE_OS::semop (this->internal_id_,
                            &ACE_SV_Semaphore_Complex::op_endcreate_[0],
                            2);
    }
  else
    {
      this->internal_id_ = ACE_OS::semget (this->key_, 2 + nsems, 0);
      if (this->internal_id_ == -1)
        return -1;


      if (ACE_OS::semop (this->internal_id_,
                         &ACE_SV_Semaphore_Complex::op_open_[0], 1) < 0)
        return this->init ();
      return 0;
    }
}
