outbound (void) const
{
  if (!this->closed_ && this->proxy_addr_)
    this->reconnect();
  if ( this->outbound_ == 0)
    return 0;
  ACE::HTBP::Channel::State s =this->outbound_->state();
  return s == ACE::HTBP::Channel::Init || s == ACE::HTBP::Channel::Ready ? this->outbound_ : 0;
}
