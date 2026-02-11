size (size_t length)
{
  ACE_TRACE ("ACE_Data_Block::size");

  if (length <= this->max_size_)
    this->cur_size_ = length;
  else
    {

      char *buf = 0;
      ACE_ALLOCATOR_RETURN (buf,
                            (char *) this->allocator_strategy_->malloc (length),
                            -1);

      ACE_OS::memcpy (buf,
                      this->base_,
                      this->cur_size_);
      if (ACE_BIT_DISABLED (this->flags_,
                            ACE_Message_Block::DONT_DELETE))
        this->allocator_strategy_->free ((void *) this->base_);
      else

        ACE_CLR_BITS (this->flags_,
                      ACE_Message_Block::DONT_DELETE);
      this->max_size_ = length;
      this->cur_size_ = length;
      this->base_ = buf;
    }
  return 0;
}
