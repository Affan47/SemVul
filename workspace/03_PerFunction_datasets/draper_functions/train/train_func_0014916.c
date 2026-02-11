get_master_system_time (time_t &time_out)
{
  ACE_TRACE ("ACE_System_Time::get_master_system_time");

  if (this->delta_time_ == 0)
    {

      void * temp = 0;
      if (this->shmem_->find (ACE_DEFAULT_TIME_SERVER_STR, temp) == -1)
        {


          return this->get_local_system_time (time_out);
        }
      else

        this->delta_time_ = static_cast<long *> (temp);
    }

  time_t local_time;


  if (*this->delta_time_ >= 0 )
    {
      this->get_local_system_time (local_time);
      time_out = local_time + static_cast<ACE_UINT32> (*this->delta_time_);
    }
  else


    time_out = *(this->delta_time_ + 1);
  return 0;
}
