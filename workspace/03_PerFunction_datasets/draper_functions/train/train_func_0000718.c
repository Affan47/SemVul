get_encoding() const
{
  xmlpp::string encoding;
  if(impl_->encoding)
    encoding = (const char*)impl_->encoding;

  return encoding;
}
