init (void)
{

  ACE_NEW_RETURN (effective_context_, ACEXML_NS_CONTEXT(), -1);

  ACEXML_String prefix (ACEXML_TABOO_NS_PREFIX, 0, false);
  ACEXML_String uri (ACEXML_XMLNS_URI_name, 0, false);
  return this->effective_context_->bind (prefix, uri);
}
