session (ACE::HTBP::Session *s)
{
  delete this->session_;
  this->session_ = s;
  s->stream (this);
}
