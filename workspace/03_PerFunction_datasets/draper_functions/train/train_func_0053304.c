get_document()const
{
  if(impl_)
    return (Document*) impl_->doc->_private;
  else
    return 0;
}
