get_namespace_uri() const
{
  if(impl_->type == XML_DOCUMENT_NODE)
  {


    return xmlpp::string();
  }

  if(impl_ && impl_->ns && impl_->ns->href)
    return (char*)impl_->ns->href;
  else
    return xmlpp::string();
}
