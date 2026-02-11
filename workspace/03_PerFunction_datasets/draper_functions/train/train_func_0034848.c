cancel (void)
{
  if (!posix_proactor_)
    return -1;
  return posix_proactor_->cancel_aio (this->handle_);
}
