rewind (void)
{
  if (this->stream_ == 0)
    return;
  this->stream_->rewind();


  if (this->stream_->seek (this->data_offset_, SEEK_SET) == -1)
    ACE_ERROR ((LM_ERROR, "%s: %m", "Error in seeking to beginning of data"));
  this->determine_encoding();
}
