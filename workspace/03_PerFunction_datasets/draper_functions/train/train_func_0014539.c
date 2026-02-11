priority_mask (u_long n_mask, MASK_TYPE mask_type)
{
  u_long o_mask;

  if (mask_type == THREAD)
    {
      o_mask = this->priority_mask_;
      this->priority_mask_ = n_mask;
    }
  else
    {
      o_mask = ACE_Log_Msg::process_priority_mask_;
      ACE_Log_Msg::process_priority_mask_ = n_mask;
    }

  return o_mask;
}
