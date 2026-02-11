data_consumed (size_t n)
{
  this->data_consumed_ += n;
  if (this->data_consumed_ == this->data_len_)
    {
      this->filter_->recv_data_trailer(this);
      this->filter_->send_ack(this);
    }
}
