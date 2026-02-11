release_underlying()
{
  if(context_)
  {
    context_->_private = 0;

    if( context_->myDoc != 0 )
    {
      xmlFreeDoc(context_->myDoc);
    }

    xmlFreeParserCtxt(context_);
    context_ = 0;
  }
}
