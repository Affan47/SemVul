register_object (const ACE_Dumpable *dumper)
{
  ACE_TRACE ("ACE_ODB::register_object");
  int i;
  int slot = 0;

  for (i = 0; i < this->current_size_; i++)
    {
      if (this->object_table_[i].this_ == 0)
        slot = i;
      else if (this->object_table_[i].this_ == dumper->this_)
        {
          slot = i;
          break;
        }
    }

  if (i == this->current_size_)
    {
      slot = this->current_size_++;
      ACE_ASSERT (this->current_size_ < ACE_ODB::MAX_TABLE_SIZE);
    }
  this->object_table_[slot].this_ = dumper->this_;
  this->object_table_[slot].dumper_ = dumper;
}
