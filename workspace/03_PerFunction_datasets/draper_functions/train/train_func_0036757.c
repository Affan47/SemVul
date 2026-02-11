recv_ack (void)
{
  if (load_buffer() == -1)
    return -1;
  return this->filter_->recv_ack(this);
}
