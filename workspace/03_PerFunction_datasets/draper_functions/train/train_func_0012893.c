end_document(void* context)
{
  _xmlParserCtxt* the_context = static_cast<_xmlParserCtxt*>(context);
  SaxParser* parser = static_cast<SaxParser*>(the_context->_private);

  if(parser->exception_)
    return;

  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  try
  {
  #endif
    parser->on_end_document();
  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  }
  catch(const exception& e)
  {
    parser->handleException(e);
  }
  #endif
}
