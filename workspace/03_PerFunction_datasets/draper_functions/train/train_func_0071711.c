locks(Task_locker* tl)
{
  tl->add(this, this->next_blocker_);
  Task_token* token = this->object_->token();
  if (token != NULL)
    tl->add(this, token);
}
